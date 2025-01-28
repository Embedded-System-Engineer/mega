#include "../../../inc/mega.h"
#if defined CSMA_MODULE
#if CSMA_MODULE

/*
 * FrameType          : Three Type Of Frame 
 */
typedef enum {
    setSerialFrame = 0,
    MangmentFrame = 1,
    DataFrame = 2,
    ControlFrame = 3
} FrameType;

/*
 * FrameSubType          : Control Frame
 */
typedef enum {
    NackFrame = 10,
    AckFrame = 11,
    BlockFrame = 12,
    FreeFrame = 13
} ControlFrameSubType;

/*
 * FrameSubType          : Management  Frame
 */
typedef enum {
    GetAddress = 10,
    AssignAddress = 11,
    RemoveAddress = 12,
    ServerConfirameRemove = 13
} ManagementFrameSubType;

/*
 * FrameSubType          : Management  Frame
 */
typedef enum {
    SerialReady = 10,
    SerialSet = 11,
    SerialDone = 12
} SerialSubType;

/*
 * FrameType          : Three Type Of Frame 
 */
typedef enum {
    FrameCode = 0,
    FrameSA = 1,
    FrameDA = 2,
    FrameActiveCode = 3,
    FrameLength = 7,
    FrameDataIndex = 8,
} FrameIndex;




/*
 ----------------------------------------------------------------------------------------------------------------
 |                  Timer Worked                                                                                |
 ----------------------------------------------------------------------------------------------------------------
 | <                                                                                                            |
 | 1- sync timer with first bit received by interrupt request the sync by reset value in                        |
 |   timer by 0 and start timer to increment bit rate after byte received (reset timer to zero and set value    |
 |   with frame parsing if any in this case mesurement the frame time and lastbyte receive Time                 |
 |  can mesurement buadrate (wire speed and detect any error between acual buadrate and design buadrate)        |
 |  T required = n  * Timer Time  ==  Frequency of Timer  = n *   Frequency Required                            |
 |  n= Frequency of Timer / Frequency Required                                                                  |      
 |  the parsing frame start after Last byte Received(TP) = xByteTime + y BitTime = (x/ByteRate) + (y/BitRate)   |
 | the bit Rate = nBit * Byte Rate == nBit is number of bit per Byte                                            |
 | TP =(nBit*x/BitRate)+(y/BitRate) = (nBit*x+y) / (BitRate)                                                    |
 | FP = 1/TP = (BitRate/(nBit*x+y)) the any Time Required when x is number of byte and y number of bit          |                                                                     
 | when the nBit Per Byte is 10 Bit and x =1 and  y = 2 BitRate = Baud rate = 19200 bps                         |
 | FP = (19200/(10*1+2)) = 1600bps == TP = 625usec =  xByteTime + y BitTime = 1*520.8+2*52.08=624.96us          |                          
 | @note 1 when any Required Time by Timer 2 from any Channel 0 or 1 can apply this eq n=(nBit*x)+y             |
 | @note 2 baud rate error detect from first start Bit enable to start BitCounte increment every Time2interrupt |
 | Frame n = has 10Byte*10Bit = 100Bit and Timer Frequency is 19200 Hz , nCount = 100 Count or nCount = 50      |
 | Frequency Required  =(BitRate/(nBit*x+y)) when nBit*x+y = number of Bit                                      |
 | Frequency Required  = 192 and nCount is 100 Count                                                            |
 | Frequency of Timer  = n *  192  = 100*192 = 19200 or 50*192 = 9600                                           |
 | when count is 50 the buad rate worked is 9600 and when count is 100 the buadrate is worked is 19200          |
 | main Function to Generate any Time  n =(nBit*x)+y when (nBit*x)+y = number of bits when x is channel number  |
 | nFrameParsingChx =   (10Bit * 1Byte)+0Bit = 10Bit time is 12*52.08us = 520.8us                               |
 | nFrameMasterBus = (10Bit*1Byte)+2Bit = 12Bit time is 12*52.08us = 624.96us                                   |
 | nFrameSlaveBus  = (10Bit*1Byte)+3Bit = 13Bit time is 677.04us when x is channel number                       |                                                                                                                      
 | Back off Time = (CW min/ sqr(Cwmax)) * CW * slot time and  slot time is 4usec,Cw min = 32 , Cw max = 1024    |
 | when CW (Contention Window) based on the number of the frame which is sent successfully                      |                                   |
 | When we have many nodes using the medium, we require small value of Back off therhlod relative to current    |
 | CW size to reduce collisionsand when we have few nodes using the medium, we require high value of backoff    |
 | to current CW size to fast collision resolution                                                              |
 | when Cw = Cw min BackOff Time is 64us and Cw = 128us and Cw = Cw max = 1024 the Bacoff time = 4096us         |                                                         
 | @case 1  the Time is   128us  + 677 us = 15 *52.08=781us                                                     |
 | @case 2  the time is  4096us  +677 us  = 92*52.08 = 4860us                                                   |
 ----------------------------------------------------------------------------------------------------------------
 */

/*
 * < @macro BIT_TIME                        : Bit time 
 */
#define  BIT_TIME                              (1000000UL/UART0_BUADRATE)/*52 us*/
/*
 * < @macro N_BITs  (nBit,x,y)              :  (nBit*x)+y   x = number of byte and y = number of bit , nBit number of bit in byte
 */
#define  N_BITs(nBit,x,y)                     (nBit*x)+y 
/*
 * < @macro  PCC(Ni,Nb,Nc,Ns)              : probability of the collision at transmission Frame 
 */
#define   PCC(Ni,Nb,Nc,Ns)                  (((Nb+Nc+Ns)/(Ni+Nb+Nc+Ns)) * Nc)
#if defined USART0_ENABLED
/*
 *< @macro       RIFS                       : Redused Inter-Frame Spacing Time 
 */
#define         RIFS                          USART0_BYTE_DURATION
#elif defined  USART1_ENABLED
/*
 *< @macro       RIFS                       : Redused Inter-Frame Spacing Time 
 */
#define         RIFS                          USART1_BYTE_DURATION
#endif
/*
 *< @macro       RIFS                       : Redused Inter-Frame Spacing Time 
 */
#define         SIFS                         RIFS
/*
 *< @macro nFrameSlaveBus                    : Distrbuited Inter-Frame Spacing Time
 */
#define         DIFS                         2UL*RIFS
/*
 * < @macro  ACKO                           : Ack time out Received 
 */
#define         ACKO                         12UL*RIFS      
/*
 * < @macro     BIFS                        : Block Inter-Frame Space
 */
#define         BIFS                         STATION_BLOCK_TIME*RIFS
/*
 *< @macro CW_MIN                            : min value of  Contention Window              
 */
#define CW_MIN                                      31
/*
 * @macro CW_MAX                             : max value of  Contention Window min 22us and max 1024us
 */
#define CW_MAX                                     1023 
#ifndef    STATION_BLOCK_TIME 
#define    STATION_BLOCK_TIME                              (50) 
#endif

#ifndef    COM_MAX_RETARY
#define    COM_MAX_RETARY                                  (10)
#endif

#ifndef   COM_PAYLOAD_SIZE                                 
#define   COM_PAYLOAD_SIZE                                 (10)
#endif
#ifndef  STATION_ASSIGN_ADDRESS
#define  STATION_ASSIGN_ADDRESS                            (0)
#endif

#define  TIMER_STATE_IDLE       (0)
#define  TIMER_STATE_RECEIVE    (1)
#define  TIMER_STATE_SEND       (2)
#define  TIMER_STATE_ACK        (3)
#define  TIMER_STATE_BLOCKING   (4)
#define  TIMER_STATE_ACKO       (5)

#define  RECEIVER_MY_FRAME  (0)
#define  RECEIVER_MY_ACK    (1)
#define  RECEIVER_OTHER     (2)


#if defined  USART1_ENABLED
#define CH0_TRANSMIT_INTERRUPT    UART1_TRANSMIT_INTERRUPT
#define CH0_RECEIVE_INTERRUPT     UART1_RECEIVE_INTERRUPT
#elif defined  USART0_ENABLED
#define CH0_TRANSMIT_INTERRUPT    UART0_TRANSMIT_INTERRUPT
#define CH0_RECEIVE_INTERRUPT     UART0_RECEIVE_INTERRUPT
#endif
/*
 *<@macro Data Index Into Buffer
 */
#define BUFFER_DATA_INDEX              8
/*
 * <@macro Max Length of Frarme  
 */
#define BUFFER_MAX_LENGTH        BUFFER_DATA_INDEX + COM_PAYLOAD_SIZE + 1 

#define  NEW_FRAME_TO_PARSING
/*
 *<@macro sucess of last Transmission 
 */
#define  SUCCESS_TRANSMISSION     (1)
/*
 *<@macro sucess of last Transmission 
 */
#define  FAIL_TRANSMISSION        (0)
/*
 * <@macro ACK tpye
 */
#define ACK_TYPE       (1)
/*
 * <@macro NACK tpye
 */
#define NACK_TYPE      (0)

/*
 * <@macro frame has error to no send
 */
#define ON_ERROR_FRAME       (0)

/*
 * <@macro fram is done To send 
 */
#define  ON_SUCCESS_FRAME     (1)
/*
 * <@macro fram is done To send 
 */
#define  ON_REMOVE_FRAME      (2)
/*
 * <@var data len
 */
static volatile uint8_t gu8OtherDeviceDA;
/*
 * <@var data len
 */
static volatile uint8_t gu8OtherDeviceSA;
/*
 * <@var data len
 */
static volatile uint8_t gu8len;
/*
 * <@var data len
 */
static uint8_t gu8CsmaUserData[COM_PAYLOAD_SIZE];
/*
 * <@var User Call back state
 */
static volatile uint8_t gu8UserReceiverState;
/*
 * <@var User Call back state
 */
static volatile uint8_t gu8UserSendState;
/*
 * <@var User Call back state
 */
static pFuncReceiveData_t gpFunResponseFrame;
/*
 * <@var OnClient Frame Exeucation
 */
static pFuncReceiveData_t gpFunDataRequest;
/*
 *<@macro Assignmemt Address of the Data
 */

static volatile uint8_t gu8CurrentAssignmetAddress;
/*
 * <@var Managment System Call back
 */
static volatile uint8_t gu8ManagmentSystemState;
/*
 * <@macro 
 */
/*
 * <@var bus State is Idle or Not 
 */
static volatile uint8_t gu8TransmitByteCounter;
/*
 * <@var bus State is Idle or Not 
 */
static volatile uint8_t gu8MaxTransmitByte;
/*
 * <@var collission Counter
 */
static volatile uint8_t gu8CoillisonCounter;
/*
 * <@var Back off Time of window 
 */
static volatile uint8_t gu8CW;
/*
 * <@ var newTransmit state can't 
 */
static volatile uint8_t gu8NewTransmitState;
/*
 *<@ var number of retry 
 */
static volatile uint8_t gu8NumberOfTry;
/*
 *< @var gu8CW              :  Contention Window Counter
 */
static volatile uint8_t gu8StationAddress;
/*
 * <@var 
 */
static volatile time_t guTLastGetAssignAddressCode;
/*
 *< @var destination  station Address              
 */
/*
 *<@var Transmit Buffer 
 */
static uint8_t gu8TransmissionBuffer[BUFFER_MAX_LENGTH];
/*
 *<@var Transmit Buffer 
 */
static uint8_t gu8TransmittAckBuffer[9];
/*
 * <@var Register this Function at transmission Frame 
 */
static pFuncParam_t gpFunOnFrameState;
/*
 * <@var uint8_t Receive Byte Counter 
 */
static volatile uint8_t gu8ReceivByteCounter;
/*
 * <@var uint8_t Receive Byte Counter 
 */
static uint8_t gu8ReceiverBuffer[BUFFER_MAX_LENGTH];
/*
 * <@var sendStateRequest 
 */
static volatile uint8_t gu8SendStateRequest;

/*
 *<@var System server state
 */
static volatile uint8_t gu8SystemServer;
/*
 * <Activation Code System
 */
static volatile time_t guTimeActtivationCode;
/*
 * <Activation Code System
 */
static volatile uint8_t gu8CurrentTimerRun;
/*
 * <@var State of save Serial
 */
static volatile uint8_t gu8SaveSerialState;
/*
 * <@var State of save Serial
 */
static volatile uint8_t gu8LoadIp;
/*
 * <@var Save serial function
 */
static pFuncPSaveSerail_t gpFunctionSaveSerial;
/*
 * <runNewAck Frame
 */
static volatile uint8_t gu8SendAckState;

static void defalutStateFun(__unused uint8_t State);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTransmitCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTransmitCallBack                                                                                   | 
 | < @Description       : this function run in ISR of receive Byte                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaTransmitCallBack(uint8_t byte);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static void ch0_usartPutByte(uint8_t byte);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ch0_usartErrorFrame();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaAckControlFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaAckControlFrame                                                                                   | 
 | < @Description       : external action of the of frame                                                              |                                                                                   
 | < @Param Type        : system Have Ack Or Not 
 * | < @return          : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaAckControlFrame(uint8_t type);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ch0_usartGetByteByte();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < csmaUserCallBack  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaUserCallBack                                                              |
 | < @Description       : Data Request and Reponse                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void csmaUserCallBack();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnSendFrame  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnSendFrame                                                              |
 | < @Description       : Frame after send Request                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void OnSendFrame(uint8_t State);

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ResetCurrentFrameSend >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ResetCurrentFrameSend                                                                                   | 
 | < @Description       : Reset current Frame                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ResetCurrentFrameSend(uint8_t State);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaMangmentCallbacks >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaMangmentCallbacks                                                                                   | 
 | < @Description       : this function run in background task                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaMangmentCallbacks();
/*
 * <Comm Filed Return Request 
 */
static stTimer_TimeOut_t gsNetWorkFiledRequest;
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntClientFrameRemoveAddess >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntClientFrameRemoveAddess                                                                                   | 
 | < @Description       : action with On Remove Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntClientFrameRemoveAddess(uint8_t State);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntClientFrameGetAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntClientFrameGetAddress                                                                                   | 
 | < @Description       : wait for Assign Address system                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntClientFrameGetAddress(uint8_t State);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntServerFrameAssignAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntServerFrameAssignAddress                                                                                   | 
 | < @Description       : handeling of the assign Frame Request                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntServerConFiarm(uint8_t State);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntServerFrameAssignAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntServerFrameAssignAddress                                                                                   | 
 | < @Description       : handeling of the assign Frame Request                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntServerFrameAssignAddress(uint8_t State);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntServerFrameRemoveAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntServerFrameRemoveAddress                                                                                   | 
 | < @Description       : handeling of the remove address  Frame Request                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntServerFrameRemoveAddress(uint8_t State);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaMangmentClientCallbacks >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaMangmentClientCallbacks                                                                                   | 
 | < @Description       : this function run at client is not have address                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaMangmentClientCallbacks();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaMangmentServerCallbacks >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaMangmentServerCallbacks                                                                                   | 
 | < @Description       : this function run at server to automatic assign address                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaMangmentServerCallbacks();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < commBackOffTime >                                                                      |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint16_t  commBackOffTime                                                                         |                 
 | < @Description       : calucation backoff time depent channel collision-based window-scaled backoff (CWSB)               |  
 | < @Param Type        : 0 the backoff time by collision state , 1 the back of time by successfully Transmission           |                                                                              
 | < @Param ID          : ChannelID                                                                                         |
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static uint16_t commBackOffTime(uint8_t Type);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendAckCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendAckCallBack                                                                                   | 
 | < @Description       : send the ack frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void sendAck(uint8_t Type, uint8_t DA, uint8_t *buf);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendAckCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendAckCallBack                                                                                   | 
 | < @Description       : send the ack frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void sendAckCallBack(uint8_t Byte);

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ParseWithMangmentFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ParseWithMangmentFrame                                                                                   | 
 | < @Description       : Parsing Frame with Mangement Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ParseWithMangmentFrame();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTimerReceiverCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTimerReceiverCallBack                                                                                   | 
 | < @Description       : this function run in every bit Rate to Transmitt Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaTimerReceiverCallBack();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ParseWithControlFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ParseWithControlFrame                                                                                   | 
 | < @Description       : Parsing Frame with Control Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ParseWithControlFrame();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < StartTimerWithTime>                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : void StartTimerWithTime                                                                          | 
 | < @Description            : set current Timer run                                                               |                                                                                   
 | < @return                 : void                                                                                    |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void StartTimerWithTime(uint16_t Time);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < csma_StartTimerV1  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csma_StartTimerV1                                                                 |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void csma_RestTimer(void);

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTimerParsingData >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTimerParsingData                                                                                   | 
 | < @Description       : Parsing Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaTimerParsingData();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaReTransmitCurrentFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaReTransmitCurrentFrame                                                                                   | 
 | < @Description       : check ReTransmit Frame Or not                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaReTransmitCurrentFrame();

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ParseWithDataFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ParseWithDataFrame                                                                                   | 
 | < @Description       : Parsing With Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ParseWithDataFrame();
/*
 ----------------------------------------------------------------------------------------------------------------
 |                               < Timer Interrupt >                                                                  |
 ----------------------------------------------------------------------------------------------------------------
 */
#if defined UART0_TRANSMIT_INTERRUPT

ISR(UART0_TRANSMIT_INTERRUPT) {
    return;
}
#endif
/* 
----------------------------------------------------------------------------------------------------------------
|                               <  Interrupt Handling >                                                                  |
----------------------------------------------------------------------------------------------------------------
 */
#if defined PCIE2   && defined (USART0_ENABLED) 
ISR(PCINT2_vect)
#elif (defined (EICRA)) && (defined (EICRB)) && defined (USART1_ENABLED)

ISR(INT2_vect)
#elif  defined (USART0_ENABLED) 

ISR(INT0_vect)
#endif
{

    csma_RestTimer();
    gu8CurrentTimerRun = (TIMER_STATE_RECEIVE);
}

ISR(CH0_RECEIVE_INTERRUPT) {


    csma_RestTimer();
    uint8_t ReceiveByte;
    ReceiveByte = ch0_usartGetByteByte();


    /*save the data into Receive buffer if is commuiaction id done */
    if (gu8ReceivByteCounter < (BUFFER_MAX_LENGTH)) {
        gu8ReceiverBuffer[gu8ReceivByteCounter] = ReceiveByte;
        switch (gu8SendStateRequest) {
            case RECEIVER_MY_FRAME:
                csmaTransmitCallBack(gu8ReceiverBuffer[gu8ReceivByteCounter]);
                break;
            case RECEIVER_MY_ACK:
                sendAckCallBack(ReceiveByte);
                break;
            case RECEIVER_OTHER:
                break;
            default:
                gu8SendStateRequest = RECEIVER_OTHER;
                break;
        }
        gu8ReceivByteCounter++;
    } else {
        gu8ReceivByteCounter = 0;
    }

    StartTimerWithTime(RIFS);
    gu8CurrentTimerRun = (TIMER_STATE_RECEIVE);

#if (defined (EICRA)) && (defined (EICRB))
#if defined USART1_ENABLED /*Interrupt 2*/
    EICRA &= ~_BV(ISC20);
    EICRA |= _BV(ISC21);
#endif
#endif

}

ISR(TIMER1_COMPA_vect) {

    csma_RestTimer();


    switch (gu8CurrentTimerRun) {
        case TIMER_STATE_IDLE:
            break;
        case TIMER_STATE_RECEIVE:
            csmaTimerReceiverCallBack();
            break;
        case TIMER_STATE_SEND:
            gu8TransmitByteCounter = 0;
            gu8ReceivByteCounter = 0;
            ch0_usartPutByte(gu8TransmissionBuffer[0]);
            gu8SendStateRequest = (RECEIVER_MY_FRAME);
            break;
        case TIMER_STATE_ACK:
            gu8TransmitByteCounter = 0;
            gu8ReceivByteCounter = 0;
            gu8SendStateRequest = (RECEIVER_MY_ACK);
            ch0_usartPutByte(gu8TransmittAckBuffer[0]);
            break;
        case TIMER_STATE_BLOCKING:
            csmaReTransmitCurrentFrame();
            break;
        case TIMER_STATE_ACKO:
            if (gu8NumberOfTry < COM_MAX_RETARY) {
                gu8NumberOfTry++;
                /*ReTransmit Frame*/
                gu8CurrentTimerRun = (TIMER_STATE_SEND);
                StartTimerWithTime(commBackOffTime(FAIL_TRANSMISSION));
                return;
            }

            gu8CurrentTimerRun = (TIMER_STATE_RECEIVE);
            gu8NewTransmitState = 0;
            gu8NumberOfTry = 0;
            if (gpFunOnFrameState != NULL && gpFunOnFrameState != defalutStateFun) {//
                sendFreeFrame();
                gpFunOnFrameState(ON_ERROR_FRAME);
            }
            /*run CallBack With Error*/
            return;
            break;
        default:
            gu8CurrentTimerRun = TIMER_STATE_RECEIVE;
            break;
    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaloadConfig >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : void csmaloadConfig                                                                          | 
 | < @Description            : load system configuration                                                                    |                                                                                   
 | < @Param serverType       : 0 the deviceType is cleint , 1 is server 
 | < @Param  ActivationCode  : code of device 
 *  | < @return              : void                                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaloadConfig(uint8_t serverType, time_t ActivationCode) {
    gu8SystemServer = serverType;
    guTimeActtivationCode = ActivationCode;
    if (gu8SystemServer) {
        gu8ManagmentSystemState = 1;
    } else {
        gu8ManagmentSystemState = 0;
    }
    srandom(ActivationCode);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < StartTimerWithTime>                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : void StartTimerWithTime                                                                          | 
 | < @Description            : set current Timer run                                                               |                                                                                   
 | < @return                 : void                                                                                    |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void StartTimerWithTime(uint16_t Time) {
    if (Time == 0)
        return;

    uint16_t freq, value;
    TCCR1B = 0x0B;
    TCCR1A = 0x00;
    freq = (uint16_t) ((1000000UL / Time) + 1UL);
    value = (uint16_t) (F_CPU / (64UL * freq));
    OCR1A = value;
    TIMSK |= _BV(OCIE1A);
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < csma_StartTimerV1  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csma_StartTimerV1                                                                 |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void csma_RestTimer(void) {
    TCCR1B = 0x00;
    TCNT1 = 0;
    TIMSK &= ~_BV(OCIE1A);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaReTransmitCurrentFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaReTransmitCurrentFrame                                                                                   | 
 | < @Description       : check ReTransmit Frame Or not                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaReTransmitCurrentFrame() {
    if (gu8NewTransmitState == 1) {
        gu8CurrentTimerRun = (TIMER_STATE_SEND);
        StartTimerWithTime(commBackOffTime(SUCCESS_TRANSMISSION));
        return;
    }

    if (gu8NewTransmitState == 2) {
        gu8CurrentTimerRun = (TIMER_STATE_ACKO);
        StartTimerWithTime(ACO);
        return;
    }
    gu8CurrentTimerRun = (TIMER_STATE_IDLE);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTimerParsingData >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTimerParsingData                                                                                   | 
 | < @Description       : Parsing Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaTimerParsingData() {
    uint8_t u8Code;

    u8Code = (gu8ReceiverBuffer[0] & 0xF0) >> 4;
    switch (u8Code) {
        case setSerialFrame:
            if ((gu8ReceiverBuffer[0] & 0x0F) != SerialReady) {
                return;
            }
            if (gu8ReceiverBuffer[FrameDA] != 0xFF) {
                return;
            }

            if (gu8ReceiverBuffer[FrameSA] != 0x00) {
                return;
            }

            if (gu8ReceiverBuffer[FrameLength] != 16) {
                return;
            }
            gu8SaveSerialState = 1;
            gu8ManagmentSystemState = 0;
            sendAck(AckFrame, 0xFF, gu8ReceiverBuffer);
            break;
        case MangmentFrame:
            ParseWithMangmentFrame(gu8ReceiverBuffer[0] & 0x0F);
            break;
        case DataFrame:
            ParseWithDataFrame(gu8ReceiverBuffer[0] & 0x0F);
            break;
        case ControlFrame:
            if (gu8ReceiverBuffer[FrameDA] != gu8StationAddress && gu8ReceiverBuffer[FrameDA] != 0xFF) {
                gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
                StartTimerWithTime(BIFS);
                return;
            }

            ParseWithControlFrame();
            break;
        default:
            csmaReTransmitCurrentFrame();
            break;
    }

}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTimerReceiverCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTimerReceiverCallBack                                                                                   | 
 | < @Description       : this function run in every bit Rate to Transmitt Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaTimerReceiverCallBack() {

    gu8TransmitByteCounter = 0;
    gu8CurrentTimerRun = TIMER_STATE_IDLE;

    switch (gu8SendStateRequest) {
        case RECEIVER_MY_FRAME:

            gu8ReceivByteCounter = 0;
            if (gu8ReceiverBuffer[FrameDA] == 0xFF) {
                /*Reset My Send Frame*/
                ResetCurrentFrameSend(ON_SUCCESS_FRAME);
                return;
            }
            gu8CurrentTimerRun = (TIMER_STATE_ACKO);
            StartTimerWithTime(ACO);
            gu8SendStateRequest = RECEIVER_OTHER;
            gu8NewTransmitState = 2;
            break;
        case RECEIVER_MY_ACK:
            gu8ReceivByteCounter = 0;
            gu8SendAckState = 0;
            gu8ReceivByteCounter = 0;
            csmaReTransmitCurrentFrame();
            if (gu8SaveSerialState) {
                gu8SaveSerialState = 0;
                if (gpFunctionSaveSerial != NULL) {
                    gpFunctionSaveSerial(gu8ReceiverBuffer);
                }
            }
            break;
        case RECEIVER_OTHER:
            if ((gu8ReceivByteCounter < FrameDataIndex + 1) || (gu8ReceivByteCounter > BUFFER_MAX_LENGTH)) {
                gu8SendAckState = 0;
                gu8ReceivByteCounter = 0;

                csmaReTransmitCurrentFrame();
                return;
            }

            gu8ReceivByteCounter = 0;
            if (gu8ReceiverBuffer[gu8ReceiverBuffer[FrameLength] - 1] != csmaCRCCheck(gu8ReceiverBuffer, gu8ReceiverBuffer[FrameLength] - 1)) {
                csmaReTransmitCurrentFrame();
                return;
            }
            /*Parsing Frame*/

            csmaTimerParsingData();

            break;
        default:
            gu8SendStateRequest = RECEIVER_OTHER;
            gu8ReceivByteCounter = 0;
            csmaReTransmitCurrentFrame();
            break;
    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ParseWithControlFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ParseWithControlFrame                                                                                   | 
 | < @Description       : Parsing Frame with Control Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ParseWithControlFrame() {
    uint8_t subType = gu8ReceiverBuffer[0] & 0x0F;
    if (subType == AckFrame) {
        if (Match_2BUF(gu8ReceiverBuffer + FrameActiveCode, (uint8_t *) & guTimeActtivationCode, 4) == 0) {
            gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
            StartTimerWithTime(BIFS);
            return;
        }

        csmaAckControlFrame(ACK_TYPE);
        return;
    }

    if (subType == NackFrame) {
        if (Match_2BUF(gu8ReceiverBuffer + FrameActiveCode, (uint8_t *) & guTimeActtivationCode, 4) == 0) {
            gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
            StartTimerWithTime(BIFS);
            return;
        }
        csmaAckControlFrame(NACK_TYPE);
        return;
    }

    if (subType == BlockFrame) {
        gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
        StartTimerWithTime(BIFS);
        return;
    }

    if (subType == FreeFrame) {
        csmaReTransmitCurrentFrame();
        return;
    }

}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ParseWithDataFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ParseWithDataFrame                                                                                   | 
 | < @Description       : Parsing With Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ParseWithDataFrame() {
    /*Just copy data*/
    if (gu8SystemServer == 0 && gu8StationAddress == 0) {/*no executed at */
        gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
        StartTimerWithTime(BIFS);
        return;
    }





    /*copy data*/



    if (gu8ReceiverBuffer[FrameDA] != gu8StationAddress && gu8ReceiverBuffer[FrameDA] != 0xFF) {
        if (gu8CsmaUserData[1] == gu8LoadIp) {
            gu8len = gu8ReceiverBuffer[FrameLength] - (FrameDataIndex + 1);
            if (gu8len <= COM_PAYLOAD_SIZE) {
                copyBuff(gu8CsmaUserData, gu8ReceiverBuffer + FrameDataIndex, gu8len);
            }
            gu8OtherDeviceDA = gu8ReceiverBuffer[FrameSA]; /*0*/
            gu8OtherDeviceSA = gu8ReceiverBuffer[FrameDA];
            if ((gu8ReceiverBuffer[0] & 0x0F) == RequestFrame) {
                gu8UserReceiverState = 1;
            } else if ((gu8ReceiverBuffer[0] & 0x0F) == ResponseFrame) {
                gu8UserReceiverState = 2;
            }
        }
        gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
        StartTimerWithTime(BIFS);
        return;
    }


    if (((gu8ReceiverBuffer[0] & 0x0F) != ResponseFrame) && ((gu8ReceiverBuffer[0] & 0x0F) != RequestFrame)) {
        if (gu8ReceiverBuffer[FrameDA] != 0xFF) {
            sendAck(NackFrame, gu8ReceiverBuffer[FrameSA], gu8ReceiverBuffer);
        } else {
            csmaReTransmitCurrentFrame();
        }
        return;
    }

    if (gu8UserReceiverState) {
        if (gu8ReceiverBuffer[FrameDA] != 0xFF) {
            sendAck(NackFrame, gu8ReceiverBuffer[FrameSA], gu8ReceiverBuffer);
        }
        return;
    }

    gu8len = (gu8ReceiverBuffer[FrameLength] - (FrameDataIndex + 1));
    if (gu8len <= COM_PAYLOAD_SIZE) {
        copyBuff(gu8CsmaUserData, gu8ReceiverBuffer + FrameDataIndex, gu8len);
    }
    gu8OtherDeviceDA = gu8ReceiverBuffer[FrameSA]; /*0*/
    gu8OtherDeviceSA = gu8ReceiverBuffer[FrameDA];

    if ((gu8ReceiverBuffer[0] & 0x0F) == ResponseFrame) {
        gu8UserReceiverState = 2;
    } else if ((gu8ReceiverBuffer[0] & 0x0F) == RequestFrame) {
        gu8UserReceiverState = 1;
    }


    if (gu8ReceiverBuffer[FrameDA] != 0xFF) {
        sendAck(AckFrame, gu8ReceiverBuffer[FrameSA], gu8ReceiverBuffer);
    } else {
        csmaReTransmitCurrentFrame();
    }

}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ParseWithMangmentFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ParseWithMangmentFrame                                                                                   | 
 | < @Description       : Parsing Frame with Mangement Data                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ParseWithMangmentFrame() {
    switch ((gu8ReceiverBuffer[0] & 0x0F)) {
        case GetAddress:
            if (gu8SystemServer == 0) {
                gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
                StartTimerWithTime(BIFS);
                return;
            }
            gu8ManagmentSystemState = 3; //server to 3
            copyBuff(&guTLastGetAssignAddressCode, gu8ReceiverBuffer + FrameActiveCode, 4);
            sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
            if (gu8ReceiverBuffer[FrameDA] != 0xFF) {
                sendAck(AckFrame, gu8ReceiverBuffer[FrameSA], gu8ReceiverBuffer);
            }
            break;
        case AssignAddress:
            if (gu8SystemServer) {
                return;
            }
            if (Match_2BUF(gu8ReceiverBuffer + FrameDataIndex + 1, (uint8_t *) & guTimeActtivationCode, 4) == 0) {
                gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
                StartTimerWithTime(BIFS);
                return;
            }
            ResetCurrentFrameSend(ON_REMOVE_FRAME);
            gu8ManagmentSystemState = 0;
            gu8StationAddress = (gu8ReceiverBuffer[FrameDataIndex]);
            gu8CurrentAssignmetAddress = gu8StationAddress;
            sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
            if (gu8ReceiverBuffer[FrameDA] != 0xFF) {
                sendAck(AckFrame, gu8ReceiverBuffer[FrameSA], gu8ReceiverBuffer);
            }
            break;
        case RemoveAddress:
            ResetCurrentFrameSend(ON_REMOVE_FRAME); /*Go To Wait State*/

            if (gu8SystemServer == 0) {
                ATOMIC_BEGIN
                gpFunOnFrameState = defalutStateFun;
                ATOMIC_END
                if (gu8ReceiverBuffer[FrameDA] == 0xFF) {
                    gu8StationAddress = 0;
                    gu8ManagmentSystemState = 3;
                    sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
                } else {
                    gu8ManagmentSystemState = 2;
                    sysSetPeriodMS(&gsNetWorkFiledRequest, 1000);
                    gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
                    StartTimerWithTime(BIFS);
                }
                return;
            }
            sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
            copyBuff(&guTLastGetAssignAddressCode, gu8ReceiverBuffer + FrameActiveCode, 4);
            gu8ManagmentSystemState = 2; /*Go to confiarme Remove*/
            sendAck(AckFrame, 0x00, gu8ReceiverBuffer);
            gu8CurrentAssignmetAddress = 1; /*Reset*/
            break;
        case ServerConfirameRemove:
            if (gu8SystemServer) {
                return;
            }
            ResetCurrentFrameSend(ON_REMOVE_FRAME);
            sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
            gu8ManagmentSystemState = 3;
            gu8StationAddress = 0; /*Remove Last address*/
            if (Match_2BUF(gu8ReceiverBuffer + FrameDataIndex, (uint8_t *) & guTimeActtivationCode, 4) == 0) {
                /*Go To */
                gu8CurrentTimerRun = (TIMER_STATE_BLOCKING);
                StartTimerWithTime(BIFS);
                return;
            }
            sendAck(AckFrame, 0x00, gu8ReceiverBuffer); /*send Ack */
            break;
        default:
            if (gu8SystemServer) {
                sendAck(NackFrame, gu8ReceiverBuffer[FrameSA], gu8ReceiverBuffer);
            }
            break;

    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendFreeFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendFreeFrame                                                                                   | 
 | < @Description       : send Free Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sendFreeFrame() {
    if (gu8NewTransmitState) {
        return (0);
    }
    if (gu8SendAckState) {
        return (0);
    }

    if (gu8CurrentTimerRun != TIMER_STATE_IDLE) {
        return (0);
    }


    sendAck(FreeFrame, 0xFF, gu8ReceiverBuffer);
    return (1);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendBlockFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendBlockFrame                                                                                   | 
 | < @Description       : send Block Frame                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sendBlockFrame() {
    if (gu8NewTransmitState) {
        return (0);
    }
    if (gu8CurrentTimerRun != TIMER_STATE_IDLE) {
        return (0);
    }
    sendAck(BlockFrame, 0xFF, gu8ReceiverBuffer);
    return (1);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaInit >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInit                                                                                | 
 | < @Description       : Init all data of the CSMA                                                 |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaInit() {

    gu8SystemServer = 1; /*default is a server*/
    guTimeActtivationCode = 0;
    gu8CurrentTimerRun = TIMER_STATE_IDLE;
    gu8SendAckState = 0;
    gu8CW = CW_MIN;
    gu8CoillisonCounter = 0;
    gu8MaxTransmitByte = 0;
    gu8NewTransmitState = 0;
    gu8StationAddress = 0;
    gu8TransmitByteCounter = 0;
    setBuff(gu8TransmissionBuffer, 0x00, BUFFER_MAX_LENGTH);
    setBuff(gu8CsmaUserData, 0x00, COM_PAYLOAD_SIZE);
    setBuff(gu8ReceiverBuffer, 0x00, BUFFER_MAX_LENGTH);
    setBuff(gu8TransmittAckBuffer, 0x00, 9);
    gu8ReceivByteCounter = 0;
    gu8SendStateRequest = RECEIVER_OTHER;
    gu8ManagmentSystemState = 0;
    gu8CurrentAssignmetAddress = 1;
    gu8UserSendState = 0;
    gu8UserReceiverState = 0;
    gpFunDataRequest = NULL;
    gpFunResponseFrame = NULL;
    gu8SaveSerialState = 0;
    gpFunctionSaveSerial = NULL;
    gu8LoadIp = 0;
    gpFunOnFrameState = defalutStateFun;

    /*External Interrupt Worked start*/
#if (defined (EICRA)) && (defined (EICRB))
#if defined USART0_ENABLED /*Interrupt 4*/
    EIMSK |= _BV(INT4);
    EICRA &= ~_BV(ISC41);
    EICRA |= _BV(ISC40);
#endif
#if defined USART1_ENABLED /*Interrupt 2*/
    EIMSK |= _BV(INT2);
    EICRA &= ~_BV(ISC20);
    EICRA |= _BV(ISC21);

#endif

#elif defined GICR
#if defined USART0_ENABLED
    MCUCR &= ~(1 << ISC01);
    MCUCR |= (1 << ISC00);
    GICR |= (1 << INT0);
#endif

#endif


}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaDriver >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaDriver                                                                                | 
 | < @Description       : run in background Task                                                 |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaDriver() {
    if (gu8LoadIp == 0) {
        return;
    }

    if (ch0_usartErrorFrame()) {
        //read cuurent 
        ch0_usartGetByteByte();
        gu8SendAckState = 0;
        gu8ReceivByteCounter = 0;
        gu8TransmitByteCounter = 0;
        sysSetPeriodMS(&gsNetWorkFiledRequest, 100);
        csmaReTransmitCurrentFrame();
        return;
    }

    csmaMangmentCallbacks();
    csmaUserCallBack();
}





/* 
 ---------------------------------------------------------------------------------------------------------
 |                      <  Basic Function Implemntions >                                                 |
 ---------------------------------------------------------------------------------------------------------   
 */

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < commBackOffTime >                                                                      |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint16_t  commBackOffTime                                                                         |                 
 | < @Description       : calucation backoff time depent channel collision-based window-scaled backoff (CWSB)               |  
 | < @Param Type        : 0 the backoff time by collision state , 1 the back of time by successfully Transmission           |                                                                              
 | < @Param ID          : ChannelID                                                                                         |
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static uint16_t commBackOffTime(uint8_t Type) {
    uint8_t cw;
    uint8_t newCw;
    uint8_t ReTry;
    uint8_t BitDuration;
#if defined USART0_ENABLED
    BitDuration = USART0_BIT_DURATION;
#endif

#if defined USART1_ENABLED
    BitDuration = USART1_BIT_DURATION;
#endif
    if (gu8SystemServer == 0) {
        if (gu8StationAddress) {
            return (DIFS + (BitDuration * 8UL * gu8StationAddress));
        }

        cw = gu8CW;
        ReTry = gu8NumberOfTry;
        if (Type) {
            newCw = max((((cw + 1) >> 1) - 1), CW_MIN);
        } else {
            newCw = min((power2(ReTry) * (cw + 1)) - 1, CW_MAX);
        }
        gu8CW = newCw;
        return (DIFS + ((map(random(), 0, RANDOM_MAX, CW_MIN, gu8CW)) * BitDuration));
    }
    return DIFS;
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < CsmaRequestNewFrame >                                                                  |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : uint16_t  CsmaRequestNewFrame                                                                |                 
 | < @Description            : Request New Frame To send Data                                                               |  
 | < @Param Code             : code of frame Type                                                                           |                                                                              
 | < @Param buffer           : buffer data to send                                                                          |
 | < @Param desAddress       : station address to receive this frame                                                        |
 | < @Param len              : number of byte used of this Frame                                                            |
 | < @Param FunOnFrameState  : Pointer to Frame Function State                                                              |
 * | < @return               : void                                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t CsmaRequestNewFrame(uint8_t Code, uint8_t *buffer, uint8_t desAddress, uint8_t len, pFuncParam_t FunOnFrameState) {




    if (gu8SendAckState) {
        return (0);
    }

    if (gu8NewTransmitState) {
        return (0);
    }


    if (gu8CurrentTimerRun != TIMER_STATE_IDLE) {
        return (0);
    }









    if (len > COM_PAYLOAD_SIZE) {
        return (1);
    }
    ATOMIC_BEGIN
    gpFunOnFrameState = FunOnFrameState;
    /*Register Call back Request*/
    gu8NewTransmitState = 1;
    gu8CurrentTimerRun = (TIMER_STATE_SEND);
    gu8TransmitByteCounter = 0;
    gu8NumberOfTry = 0; /*reset the counter of the Number Of Try*/
    gu8TransmissionBuffer[FrameCode] = Code;
    gu8TransmissionBuffer[FrameSA] = gu8StationAddress;
    gu8TransmissionBuffer[FrameDA] = desAddress;
    copyBuff(gu8TransmissionBuffer + FrameActiveCode, &guTimeActtivationCode, 4);
    if (len && buffer != NULL) {
        copyBuff(gu8TransmissionBuffer + FrameDataIndex, buffer, len);
    }
    gu8MaxTransmitByte = FrameDataIndex + len + 1;
    gu8TransmissionBuffer[FrameLength] = gu8MaxTransmitByte;
    gu8TransmissionBuffer[FrameDataIndex + len] = csmaCRCCheck(gu8TransmissionBuffer, FrameDataIndex + len);
    StartTimerWithTime(commBackOffTime(SUCCESS_TRANSMISSION));
    ATOMIC_END

    return (1);
}





/**/

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTransmitCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTransmitCallBack                                                                                   | 
 | < @Description       : this function run in ISR of receive Byte                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaTransmitCallBack(uint8_t byte) {
    if (gu8TransmissionBuffer[gu8TransmitByteCounter] != byte) {
        gu8CoillisonCounter++;
        gu8TransmitByteCounter = 0;
        gu8SendStateRequest = (RECEIVER_OTHER); /*change state from my send to receive other*/
        return;
    }
    gu8TransmitByteCounter++;
    if (gu8TransmitByteCounter < gu8MaxTransmitByte) {
        ch0_usartPutByte(gu8TransmissionBuffer[gu8TransmitByteCounter]);
    } else {
        gu8TransmitByteCounter = 0;
        gu8CoillisonCounter = 0;
    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ResetCurrentFrameSend >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void ResetCurrentFrameSend                                                                                   | 
 | < @Description       : Reset current Frame                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void ResetCurrentFrameSend(uint8_t State) {
    csma_RestTimer();
    gu8CurrentTimerRun = TIMER_STATE_IDLE;
    gu8NewTransmitState = 0;
    gu8NumberOfTry = 0;
    gu8TransmitByteCounter = 0;
    if (gpFunOnFrameState != NULL && gpFunOnFrameState != defalutStateFun) {
        gpFunOnFrameState(State);
    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaAckControlFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaAckControlFrame                                                                                   | 
 | < @Description       : external action of the of frame                                                              |                                                                                   
 | < @Param Type        : system Have Ack Or Not 
 * | < @return          : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaAckControlFrame(uint8_t type) {
    if (type == ACK_TYPE) {
        /*run call back*/
        gu8CurrentTimerRun = (TIMER_STATE_IDLE);
        ResetCurrentFrameSend(ON_SUCCESS_FRAME);
        return;
    }
    if (type == NACK_TYPE) {
        gu8TransmitByteCounter = 0;
        gu8CurrentTimerRun = (TIMER_STATE_ACKO);
        StartTimerWithTime(ACKO);
        gu8CoillisonCounter = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static void ch0_usartPutByte(uint8_t byte) {
#if defined USART1_ENABLED 
    usart1PutByte(byte);
#elif defined USART0_ENABLED
    usart0PutByte(byte);
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ch0_usartGetByteByte() {
#if defined USART1_ENABLED 
    return (usart1GetByte());
#elif defined USART0_ENABLED
    return (usart0GetByte());
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ch0_usartErrorFrame() {
#if defined  USART0_ENABLED
    return (UARTDataFramError0());
#endif

#if defined  USART1_ENABLED
    return (UARTDataFramError1());
#endif
    return (1);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaGetMaxAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaGetMaxAddress                                                           | 
 | < @Description       : return max assignment address                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t csmaGetMaxAddress() {
    return (gu8CurrentAssignmetAddress);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaGetStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaGetStationAddress                                                           | 
 | < @Description       : get value of the address                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t csmaGetStationAddress() {
    return (gu8StationAddress);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendAckCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendAckCallBack                                                                                   | 
 | < @Description       : send the ack frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void sendAckCallBack(uint8_t Byte) {
    if (gu8TransmittAckBuffer[gu8TransmitByteCounter] != Byte) {
        gu8SendAckState = 0;
        gu8TransmitByteCounter = 0;
        gu8SendStateRequest = (RECEIVER_OTHER);
        return;
    }
    gu8TransmitByteCounter++;
    if (gu8TransmitByteCounter < 9) {
        ch0_usartPutByte(gu8TransmittAckBuffer[gu8TransmitByteCounter]);
    } else {
        /*check for My Frame after ack Received the timer state */
        gu8SendAckState = 0;
        gu8TransmitByteCounter = 0;
        return;

    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendAckCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendAckCallBack                                                                                   | 
 | < @Description       : send the ack frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void sendAck(uint8_t Type, uint8_t DA, uint8_t * buf) {
    gu8TransmitByteCounter = 0;
    gu8SendAckState = 1;
    gu8TransmittAckBuffer[0] = ((ControlFrame << 4) | Type);
    gu8TransmittAckBuffer[1] = csmaGetStationAddress();
    gu8TransmittAckBuffer[2] = DA;

    copyBuff((gu8TransmittAckBuffer + 3), buf + FrameActiveCode, 4);
    gu8TransmittAckBuffer[7] = 9;
    gu8TransmittAckBuffer[8] = csmaCRCCheck(gu8TransmittAckBuffer, 8);
    gu8CurrentTimerRun = (TIMER_STATE_ACK);
    StartTimerWithTime(SIFS);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaMangmentClientCallbacks >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaMangmentClientCallbacks                                                                                   | 
 | < @Description       : this function run at client is not have address                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaMangmentClientCallbacks() {
    uint8_t Code;
    uint8_t Type;

    if (gu8StationAddress) {
        gu8ManagmentSystemState = 0;
        return;
    }

    switch (gu8ManagmentSystemState) {
        case 0:
            sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
            gu8ManagmentSystemState = 1;
            break;
        case 1:/*send Remove Address*/
            Type = gu8SystemServer;
            Code = (MangmentFrame << 4 | RemoveAddress);
            if (CsmaRequestNewFrame(Code, &Type, 0x00, 1, OnMangemntClientFrameRemoveAddess)) {
                sysSetPeriodMS(&gsNetWorkFiledRequest, 5000); /*wait for 5seconde to just send On Frame*/
                gu8ManagmentSystemState = 2;
            }
            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {/*wait Form 5sec*/
                gu8SendAckState = 0;
                gu8NewTransmitState = 0;
                gu8CurrentTimerRun = TIMER_STATE_IDLE;
                gu8ManagmentSystemState = 0;
            }
            break;
        case 2:
            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {/*wait Form 5sec*/
                gu8ManagmentSystemState = 0; /*Repat*/
            }
            break;
        case 3://wait request
            Code = (MangmentFrame << 4 | GetAddress);
            if (CsmaRequestNewFrame(Code, NULL, 0x00, 0, OnMangemntClientFrameGetAddress)) {
                gu8ManagmentSystemState = 4;
            }

            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {
                gu8SendAckState = 0;
                gu8NewTransmitState = 0;
                gu8CurrentTimerRun = TIMER_STATE_IDLE;
                sysSetPeriodMS(&gsNetWorkFiledRequest, 500);
                gu8ManagmentSystemState = 4;
            }
            break;
        case 4://wait response
            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {
                sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
                gu8ManagmentSystemState = 3;
            }
            break;
        default:
            gu8ManagmentSystemState = 0;
            break;
    }
}

static void defalutStateFun(__unused uint8_t State) {
    return;
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntClientFrameRemoveAddess >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntClientFrameRemoveAddess                                                                                   | 
 | < @Description       : action with On Remove Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntClientFrameRemoveAddess(__unused uint8_t State) {
    ATOMIC_BEGIN
    gpFunOnFrameState = defalutStateFun; /*Remove LastRequest*/
    ATOMIC_END
    gu8StationAddress = (0);
    gu8ManagmentSystemState = 2; /*Wait For ConFirame Remove*/
    sysSetPeriodMS(&gsNetWorkFiledRequest, 100);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntClientFrameGetAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntClientFrameGetAddress                                                                                   | 
 | < @Description       : wait for Assign Address system                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntClientFrameGetAddress(uint8_t State) {
    ATOMIC_BEGIN
    gpFunOnFrameState = defalutStateFun;
    ATOMIC_END
    if (State == ON_SUCCESS_FRAME) {
        sysSetPeriodMS(&gsNetWorkFiledRequest, 100); /*Wait for 100 to repeat*/
        gu8ManagmentSystemState = 4;
        return;
    }

    if (State == ON_REMOVE_FRAME) {
        gu8StationAddress = 0;
        gu8ManagmentSystemState = 2; /*go to send system state*/
        sysSetPeriodMS(&gsNetWorkFiledRequest, 500); /*Go */
        return;
    }


    gu8ManagmentSystemState = 4;
    sysSetPeriodMS(&gsNetWorkFiledRequest, 500);


}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntServerFrameAssignAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntServerFrameAssignAddress                                                                                   | 
 | < @Description       : handeling of the assign Frame Request                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntServerFrameAssignAddress(uint8_t State) {
    ATOMIC_BEGIN
    gpFunOnFrameState = defalutStateFun;
    ATOMIC_END
    if (State == ON_SUCCESS_FRAME) {
        gu8CurrentAssignmetAddress++;
        gu8ManagmentSystemState = 0;
        if (gu8CurrentAssignmetAddress >= 128) {
            gu8CurrentAssignmetAddress = 1;
            gu8ManagmentSystemState = 1;
            sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
            return;
        }
        return;
    }


    if (State == ON_REMOVE_FRAME) {
        sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
        gu8CurrentAssignmetAddress = 1;
        gu8ManagmentSystemState = 0; /*go to send system state*/
        return;
    }

    if (State == ON_ERROR_FRAME) {
        sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
        gu8ManagmentSystemState = 0; /*go to send system state*/
    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntServerFrameRemoveAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntServerFrameRemoveAddress                                                                                   | 
 | < @Description       : handeling of the remove address  Frame Request                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntServerFrameRemoveAddress(__unused uint8_t State) {
    ATOMIC_BEGIN
    gpFunOnFrameState = defalutStateFun;
    ATOMIC_END
    gu8ManagmentSystemState = 0; /*go to send system state*/
    gu8CurrentAssignmetAddress = 1;
    sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < OnMangemntServerFrameAssignAddress >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void OnMangemntServerFrameAssignAddress                                                                                   | 
 | < @Description       : handeling of the assign Frame Request                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void OnMangemntServerConFiarm(__unused uint8_t State) {
    ATOMIC_BEGIN
    gpFunOnFrameState = defalutStateFun;
    ATOMIC_END
    sysSetPeriodMS(&gsNetWorkFiledRequest, 5000);
    gu8CurrentAssignmetAddress = 1;
    gu8ManagmentSystemState = 0; /*go to send system state*/
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaMangmentServerCallbacks >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaMangmentServerCallbacks                                                                                   | 
 | < @Description       : this function run at server to automatic assign address                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaMangmentServerCallbacks() {
    uint8_t Code;
    uint8_t buf[5];
    switch (gu8ManagmentSystemState) {
        case 0:
            break;
        case 1:/*send Remove Address*/
            Code = (MangmentFrame << 4 | RemoveAddress);
            if (CsmaRequestNewFrame(Code, NULL, 0xFF, 0, OnMangemntServerFrameRemoveAddress)) {
                gu8ManagmentSystemState = 0;
            }
            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {
                gu8ManagmentSystemState = 0;
            }
            break;
        case 2:/*send ConFirame */
            Code = (MangmentFrame << 4 | ServerConfirameRemove);
            copyBuff(buf, &guTLastGetAssignAddressCode, 4);
            if (CsmaRequestNewFrame(Code, buf, 0x00, 4, OnMangemntServerConFiarm)) {
                gu8ManagmentSystemState = 0;
            }
            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {
                gu8ManagmentSystemState = 0;
            }
            break;
        case 3:/*Assign address*/
            Code = (MangmentFrame << 4 | AssignAddress);
            buf[0] = gu8CurrentAssignmetAddress;
            copyBuff(buf + 1, &guTLastGetAssignAddressCode, 4);
            if (CsmaRequestNewFrame(Code, buf, 0x00, 5, OnMangemntServerFrameAssignAddress)) {
                gu8ManagmentSystemState = 0;
            }
            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {
                gu8ManagmentSystemState = 0;
            }
            break;
        default:
            gu8ManagmentSystemState = 0;
            break;

    }
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaMangmentCallbacks >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaMangmentCallbacks                                                                                   | 
 | < @Description       : this function run in background task                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void csmaMangmentCallbacks() {
    if (guTimeActtivationCode == 0) {
        return;
    }
    if (gu8SystemServer) {
        csmaMangmentServerCallbacks();
    } else {
        csmaMangmentClientCallbacks();
    }
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnHostFrame  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnHostFrameV1                                                              |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnHostFrameCh0(pFuncReceiveData_t receiveFrame) {
    gpFunDataRequest = receiveFrame;
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnClientFrame  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnClientFrameV1                                                            |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnClientFrameCh0(pFuncReceiveData_t receiveFrame) {
    gpFunResponseFrame = receiveFrame;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param buf         : Pointer To data send Run                                                       |  
 | < @Param len         : number of byte to send  ID                                                     |
 | < @Param DA          : Destination station address                                                    |
 | < @Param Type        : Data Request or response                                                       |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
uint8_t putDataCh0(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type) {
    uint8_t Code;

    if (guTimeActtivationCode == 0) {
        gu8UserSendState = 0;
        return (DATA_FRAME_ERROR);
    }

    if (gu8StationAddress == 0 && gu8SystemServer == 0) {
        gu8UserSendState = 0;
        return (DATA_FRAME_ERROR);
    }


    switch (gu8UserSendState) {
        case 0:
            sysSetPeriodMS(&gsNetWorkFiledRequest, 5000); /*wait Fro Bus Ready*/
            gu8UserSendState = 1;
            break;
        case 1:
            Code = ((DataFrame << 4) | (Type));
            if (CsmaRequestNewFrame(Code, buf, DA, len, OnSendFrame)) {
                sysSetPeriodMS(&gsNetWorkFiledRequest, 5000); /*Start Wait Response */
                gu8UserSendState = 2;
            }

            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {
                gu8UserSendState = 0;
                gu8SendAckState = 0;
                gu8NewTransmitState = 0;
                gu8CurrentTimerRun = TIMER_STATE_IDLE;
                return (DATA_FRAME_ERROR);
            }
            break;
        case 2:/*wait for 20second*/
            if (sysIsTimeoutMs(&gsNetWorkFiledRequest) == 0) {
                gu8UserSendState = 0;
                gu8UserSendState = 0;
                gu8SendAckState = 0;
                gu8NewTransmitState = 0;
                gu8CurrentTimerRun = TIMER_STATE_IDLE;
                return (DATA_FRAME_ERROR);
            }
            break;
        case 3:
            gu8UserSendState = 0;
            return (DATA_FRAME_SUCESS);
        case 4:
            gu8UserSendState = 0;
            return (DATA_FRAME_ERROR);
            break;
        default:
            gu8UserSendState = 0;
            break;
    }

    return (0);
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnSendFrame  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnSendFrame                                                              |
 | < @Description       : Frame after send Request                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void OnSendFrame(uint8_t State) {
    ATOMIC_BEGIN
    gpFunOnFrameState = defalutStateFun;
    ATOMIC_END
    if (State == ON_SUCCESS_FRAME) {
        gu8UserSendState = 3;
        return;
    }

    if (State == ON_REMOVE_FRAME) {
        gu8UserSendState = 3;
        return;
    }

    if (State == ON_ERROR_FRAME) {
        gu8UserSendState = 4;
        return;
    }

    gu8UserSendState = 4;
    return;
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < csmaUserCallBack  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaUserCallBack                                                              |
 | < @Description       : Data Request and Reponse                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void csmaUserCallBack() {

    if (guTimeActtivationCode == 0) {
        gu8UserReceiverState = 0;
        return;
    }

    if (gu8StationAddress == 0 && gu8SystemServer == 0) {
        gu8UserReceiverState = 0;
        return;
    }



    if (gu8SendAckState) {
        return;
    }

    switch (gu8UserReceiverState) {
        case 0:
            break;
        case 1:
            if (gpFunDataRequest != NULL) {
                if (gpFunDataRequest(gu8OtherDeviceSA, gu8OtherDeviceDA, gu8len, gu8CsmaUserData)) {

                    gu8UserReceiverState = 0;
                }
            } else {
                gu8UserReceiverState = 0;
            }
            break;
        case 2:
            if (gpFunResponseFrame != NULL) {
                if (gpFunResponseFrame(gu8OtherDeviceSA, gu8OtherDeviceDA, gu8len, gu8CsmaUserData)) {
                    gu8UserReceiverState = 0;
                }
            } else {
                gu8UserReceiverState = 0;
            }
            break;
        default:

            gu8UserReceiverState = 0;
            break;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < csmaSaveSerialRegister >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function                 : void csmaSaveSerialRegister                                                         |                                          
 | < @Description              : save serial call back function                                                      |                                                     |  
 | < @Param x                  : Pointer to function                                     |                                                  |                                                 |
 | < @return                  : void                                                                      |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
void csmaSaveSerialRegister(pFuncPSaveSerail_t x) {
    gpFunctionSaveSerial = x;
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaInitStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInitStationAddress                                                           | 
 | < @Description       : load last address after reboot                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaInitStationIp(uint8_t Ip) {
    gu8LoadIp = Ip;
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaInitStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInitStationAddress                                                           | 
 | < @Description       : load last address after reboot                                              |                                                                                   
 | < @return            : void                                                                                              |
------------------------------------------------------------------------------------------------------------
 */
void csmaInitStationAddress(uint8_t address) {
    gu8StationAddress = address;
}

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaInitStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInitStationAddress                                                           | 
 | < @Description       : load last address after reboot                                              |                                                                                   
 | < @return            : void                                                                                              |
------------------------------------------------------------------------------------------------------------
 */
void clearCurrentDataFrame() {
    if (gu8UserSendState == 1 || gu8UserSendState == 2) {
        gu8UserSendState = 0;
        ResetCurrentFrameSend(ON_REMOVE_FRAME);
    }
}
#endif
#endif