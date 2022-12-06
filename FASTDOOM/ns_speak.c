#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include "ns_dpmi.h"
#include "ns_task.h"
#include "ns_cards.h"
#include "ns_user.h"
#include "ns_speak.h"
#include "ns_muldf.h"

#include "m_misc.h"
#include "options.h"
#include "doomstat.h"

static int PCSpeaker_Installed = 0;

static char *PCSpeaker_BufferStart;
static char *PCSpeaker_CurrentBuffer;
static int PCSpeaker_BufferNum = 0;
static int PCSpeaker_NumBuffers = 0;
static int PCSpeaker_TransferLength = 0;
static int PCSpeaker_CurrentLength = 0;

static char *PCSpeaker_SoundPtr;
volatile int PCSpeaker_SoundPlaying;

static task *PCSpeaker_Timer;

void (*PCSpeaker_CallBack)(void);

/*---------------------------------------------------------------------
   Function: PCSpeaker_ServiceInterrupt

   Handles interrupt generated by sound card at the end of a voice
   transfer.  Calls the user supplied callback function.
---------------------------------------------------------------------*/

static void PCSpeaker_ServiceInterrupt(task *Task)
{
    if (*PCSpeaker_SoundPtr > -128)
    {
        unsigned char value = (unsigned char) *PCSpeaker_SoundPtr;
        value >>= 6;
        value &= 2;

        // Turn on
        OutByte61h((inp(0x61) & 0xFC) | value);
    }
    else
    {
        // Turn off
        OutByte61h(inp(0x61) & 0xFC);
    }

    PCSpeaker_SoundPtr++;

    PCSpeaker_CurrentLength--;
    if (PCSpeaker_CurrentLength == 0)
    {
        // Keep track of current buffer
        PCSpeaker_CurrentBuffer += PCSpeaker_TransferLength;
        PCSpeaker_BufferNum++;
        if (PCSpeaker_BufferNum >= PCSpeaker_NumBuffers)
        {
            PCSpeaker_BufferNum = 0;
            PCSpeaker_CurrentBuffer = PCSpeaker_BufferStart;
        }

        PCSpeaker_CurrentLength = PCSpeaker_TransferLength;
        PCSpeaker_SoundPtr = PCSpeaker_CurrentBuffer;

        // Call the caller's callback function
        if (PCSpeaker_CallBack != NULL)
        {
            MV_ServiceVoc();
        }
    }
}

/*---------------------------------------------------------------------
   Function: PCSpeaker_StopPlayback

   Ends the transfer of digitized sound to the Sound Source.
---------------------------------------------------------------------*/

void PCSpeaker_StopPlayback(void)
{
    if (PCSpeaker_SoundPlaying)
    {
        // Turn off
        OutByte61h(inp(0x61) & 0xFC);
        TS_Terminate(PCSpeaker_Timer);
        PCSpeaker_SoundPlaying = 0;
        PCSpeaker_BufferStart = NULL;
    }
}

/*---------------------------------------------------------------------
   Function: PCSpeaker_BeginBufferedPlayback

   Begins multibuffered playback of digitized sound on the Sound Source.
---------------------------------------------------------------------*/

int PCSpeaker_BeginBufferedPlayback(
    char *BufferStart,
    int BufferSize,
    int NumDivisions,
    void (*CallBackFunc)(void))
{
    if (PCSpeaker_SoundPlaying)
    {
        PCSpeaker_StopPlayback();
    }

    PCSpeaker_CallBack = CallBackFunc;

    PCSpeaker_BufferStart = BufferStart;
    PCSpeaker_CurrentBuffer = BufferStart;
    PCSpeaker_SoundPtr = BufferStart;
    // VITI95: OPTIMIZE
    PCSpeaker_TransferLength = BufferSize / NumDivisions;
    PCSpeaker_CurrentLength = PCSpeaker_TransferLength;
    PCSpeaker_BufferNum = 0;
    PCSpeaker_NumBuffers = NumDivisions;

    PCSpeaker_SoundPlaying = 1;

    PCSpeaker_Timer = TS_ScheduleTask(PCSpeaker_ServiceInterrupt, PCSpeaker_SampleRate, 1, NULL);
    TS_Dispatch();

    return (PCSpeaker_Ok);
}

/*---------------------------------------------------------------------
   Function: PCSpeaker_Init

   Initializes the Sound Source prepares the module to play digitized
   sounds.
---------------------------------------------------------------------*/

int PCSpeaker_Init(int soundcard)
{
    if (PCSpeaker_Installed)
    {
        PCSpeaker_Shutdown();
    }

    PCSpeaker_SoundPlaying = 0;

    PCSpeaker_CallBack = NULL;

    PCSpeaker_BufferStart = NULL;

    PCSpeaker_Installed = 1;

    return (PCSpeaker_Ok);
}

/*---------------------------------------------------------------------
   Function: PCSpeaker_Shutdown

   Ends transfer of sound data to the Sound Source.
---------------------------------------------------------------------*/

void PCSpeaker_Shutdown(void)
{
    PCSpeaker_StopPlayback();

    PCSpeaker_SoundPlaying = 0;

    PCSpeaker_BufferStart = NULL;

    PCSpeaker_CallBack = NULL;

    PCSpeaker_Installed = 0;
}
