#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;

const char* g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char* g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateMachine(State state, Action action)
{
    setState(state);
    setAction(action);
}

FocusState AppControl::getFocusState()
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)
{
    m_focus_state = fs;
}

void AppControl::displayTitleInit()
{
    mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH, TITLE_X_CRD, TITLE_Y_CRD);
}

void AppControl::displayMenuInit()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH, MENU_UP_X_CRD, MENU_UP_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH, MENU_DECIDE_X_CRD, MENU_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH, MENU_DOWN_X_CRD, MENU_DOWN_Y_CRD);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{
    switch(current_state){
        case MENU_WBGT:
            mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
        break;

        case MENU_MUSIC:
            mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
        break;

        case MENU_MEASURE:
            mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
        break;

        case MENU_DATE:
            mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
        break;
    }

        switch(next_state){
        case MENU_WBGT:
            mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
        break;

        case MENU_MUSIC:
            mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
        break;

        case MENU_MEASURE:
            mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
        break;

        case MENU_DATE:
            mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
        break;
    }
}

void AppControl::displayWBGTInit()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mwbgt.init();
    displayTempHumiIndex();
}

void AppControl::displayTempHumiIndex()
{
    double temperature, humidity;
    WbgtIndex wbgt_state;
    mwbgt.getWBGT(&temperature, &humidity, &wbgt_state);

    int divisor = 10;
    int tenfold_temperature = temperature * 10;
    int tenfold_humidity = humidity * 10;

    mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, WBGT_TEMPERATURE_X_CRD, WBGT_TEMPERATURE_Y_CRD);

    for(int display_cnt = 1; display_cnt <= 3; display_cnt++){
        switch(display_cnt){
            case 1:
                mlcd.displayJpgImageCoordinate(g_str_orange[tenfold_temperature % divisor], WBGT_T1DECIMAL_X_CRD, WBGT_T1DECIMAL_Y_CRD);                    
                break;

            case 2:
                mlcd.displayJpgImageCoordinate(g_str_orange[tenfold_temperature % divisor], WBGT_T1DIGIT_X_CRD, WBGT_T1DIGIT_Y_CRD); 
                break;

            case 3:
                if(tenfold_temperature % divisor == 0){
                    mlcd.displayJpgImageCoordinate(COMMON_ORANGEFILLWHITE_IMG_PATH, WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);
                } else {
                    mlcd.displayJpgImageCoordinate(g_str_orange[tenfold_temperature % divisor], WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD); 
                }
                break;
        }
        tenfold_temperature = tenfold_temperature / 10;
    }

    mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, WBGT_TDOT_X_CRD, WBGT_TDOT_Y_CRD);
    mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, WBGT_DEGREE_X_CRD, WBGT_DEGREE_Y_CRD);

    mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, WBGT_HUMIDITY_X_CRD, WBGT_HUMIDITY_Y_CRD);

    for(int display_cnt = 1; display_cnt <= 3; display_cnt++){
        switch(display_cnt){
            case 1:
                mlcd.displayJpgImageCoordinate(g_str_blue[tenfold_humidity % divisor], WBGT_H1DECIMAL_X_CRD, WBGT_H1DECIMAL_Y_CRD);                    
                break;

            case 2:
                mlcd.displayJpgImageCoordinate(g_str_blue[tenfold_humidity % divisor], WBGT_H1DIGIT_X_CRD, WBGT_H1DIGIT_Y_CRD); 
                break;

            case 3:
                if(tenfold_humidity % divisor == 0){
                    mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD); 
                } else {
                    mlcd.displayJpgImageCoordinate(g_str_blue[tenfold_humidity % divisor], WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD); 
                }
                break;
        }
        tenfold_humidity = tenfold_humidity / 10;
    }

    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, WBGT_HDOT_X_CRD, WBGT_HDOT_Y_CRD);
    mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, WBGT_PERCENT_X_CRD, WBGT_PERCENT_Y_CRD);

    switch(wbgt_state) {
        case SAFE:
            mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
        break;

        case ATTENTION:
            mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
        break;

        case ALERT:
            mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
        break;

        case HIGH_ALERT:
            mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
        break;

        case DANGER:
            mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH, WBGT_NOTICE_X_CRD, WBGT_NOTICE_Y_CRD);
        break;

    }

    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, WBGT_BACK_X_CRD, WBGT_BACK_Y_CRD);
}

void AppControl::displayMusicInit()
{
    displayMusicStop();
    displayMusicTitle();
}

void AppControl::displayMusicStop()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH, MUSIC_NOTICE_X_CRD, MUSIC_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, MUSIC_PLAY_X_CRD, MUSIC_PLAY_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, MUSIC_BACK_X_CRD, MUSIC_BACK_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, MUSIC_NEXT_X_CRD, MUSIC_NEXT_Y_CRD);
}

void AppControl::displayMusicTitle()
{
    mlcd.displayText(mmplay.getTitle(), MUSIC_TITLE_X_CRD, MUSIC_TITLE_Y_CRD);
}

void AppControl::displayNextMusic()
{
    mmplay.selectNextMusic();
    // displayMusicStop();
    mlcd.displayText("                    ", MUSIC_TITLE_X_CRD, MUSIC_TITLE_Y_CRD);
    displayMusicTitle();
}

void AppControl::displayMusicPlay()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH, MUSIC_NOTICE_X_CRD, MUSIC_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH, MUSIC_STOP_X_CRD, MUSIC_STOP_Y_CRD);
    displayMusicTitle();
}

void AppControl::displayMeasureInit()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH, MEASURE_NOTICE_X_CRD, MEASURE_NOTICE_Y_CRD);
    displayMeasureDistance();
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, MEASURE_BACK_X_CRD, MEASURE_BACK_Y_CRD);
}

void AppControl::displayMeasureDistance()
{
    int measurement_distance = mmdist.getDistance() * 10;
    int divisor = 10;

    for(int display_cnt = 1; display_cnt <= 4; display_cnt++){
        switch(display_cnt){
            case 1:
                mlcd.displayJpgImageCoordinate(g_str_blue[measurement_distance % divisor], MEASURE_DECIMAL_X_CRD, MEASURE_DECIMAL_Y_CRD);                    
                break;

            case 2:
                mlcd.displayJpgImageCoordinate(g_str_blue[measurement_distance % divisor], MEASURE_DIGIT1_X_CRD, MEASURE_DIGIT1_Y_CRD); 
                break;

            case 3:
                if((measurement_distance% divisor == 0) && ((measurement_distance / divisor) % divisor == 0)){
                    mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);
                } else {
                    mlcd.displayJpgImageCoordinate(g_str_blue[measurement_distance % divisor], MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);
                }
                break;

            case 4:
                if(measurement_distance% divisor == 0){
                    mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, MEASURE_DIGIT3_X_CRD, MEASURE_DIGIT3_Y_CRD);
                } else {
                    mlcd.displayJpgImageCoordinate(g_str_blue[measurement_distance % divisor], MEASURE_DIGIT3_X_CRD, MEASURE_DIGIT3_Y_CRD); 
                }
                break;
        }
        measurement_distance = measurement_distance / 10;
    }

    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, MEASURE_DOT_X_CRD, MEASURE_DOT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH, MEASURE_CM_X_CRD, MEASURE_CM_Y_CRD); 

}

void AppControl::displayDateInit()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, DATE_NOTICE_X_CRD, DATE_NOTICE_Y_CRD);
    displayDateUpdate();
}

void AppControl::displayDateUpdate()
{
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, DATE_NOTICE_X_CRD, DATE_NOTICE_Y_CRD);
    mlcd.displayDateText(mdtime.readDate(), DATE_YYYYMMDD_X_CRD, DATE_YYYYMMDD_Y_CRD);
    mlcd.displayDateText(mdtime.readTime(), DATE_HHmmSS_X_CRD, DATE_HHmmSS_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATE_BACK_X_CRD, DATE_BACK_Y_CRD);
}

void AppControl::controlApplication()
{
    mmplay.init();
    bool play_flg;

    while (1) {

        switch (getState()) {
        case TITLE:
            switch (getAction()) {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
                Serial.println("TITLE ENTRY");
                displayTitleInit();
                setStateMachine(TITLE, DO);
                break;

            case DO:
                if(m_flag_btnA_is_pressed == true || m_flag_btnB_is_pressed == true || m_flag_btnC_is_pressed == true){
                    setStateMachine(TITLE, EXIT);
                    setBtnAllFlgFalse();
                }
                Serial.println("TITLE DO");
                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                Serial.println("TITLE EXIT");
                break;

            default:
                break;
            }

            break;

        case MENU:

            switch (getAction()) {
            case ENTRY:
                displayMenuInit();
                setStateMachine(MENU, DO);
                Serial.println("MENU ENTRY");

                break;

            case DO:
                Serial.println("MENU DO");
                if(m_flag_btnA_is_pressed == true){
                    switch (getFocusState()) {
                        case MENU_WBGT:
                            focusChangeImg(MENU_WBGT, MENU_DATE);
                            setFocusState(MENU_DATE);
                            break;
                        
                        case MENU_MUSIC:
                            focusChangeImg(MENU_MUSIC, MENU_WBGT);
                            setFocusState(MENU_WBGT);
                            break;
                        
                        case MENU_MEASURE:
                            focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                            setFocusState(MENU_MUSIC);
                            break;
                        
                        case MENU_DATE:
                            focusChangeImg(MENU_DATE, MENU_MEASURE);
                            setFocusState(MENU_MEASURE);
                            break;
                    }
                    setBtnAllFlgFalse();                    
                }
                else if(m_flag_btnC_is_pressed == true) {
                    switch (getFocusState()) {
                        case MENU_WBGT:
                            focusChangeImg(MENU_WBGT, MENU_MUSIC);
                            setFocusState(MENU_MUSIC);
                            break;
                        
                        case MENU_MUSIC:
                            focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                            setFocusState(MENU_MEASURE);
                            break;
                        
                        case MENU_MEASURE:
                            focusChangeImg(MENU_MEASURE, MENU_DATE);
                            setFocusState(MENU_DATE);
                            break;
                        
                        case MENU_DATE:
                            focusChangeImg(MENU_DATE, MENU_WBGT);
                            setFocusState(MENU_WBGT);
                            break;
                    }
                    setBtnAllFlgFalse();
                }
                else if(m_flag_btnB_is_pressed == true) {
                    setStateMachine(MENU, EXIT);
                    setBtnAllFlgFalse();
                }
                break;

            case EXIT:
                Serial.println("MENU EXIT");
                switch (getFocusState()) {
                    case MENU_WBGT:
                        setStateMachine(WBGT, ENTRY);
                    break;
                        
                    case MENU_MUSIC:
                        setStateMachine(MUSIC_STOP, ENTRY);
                    break;
                        
                    case MENU_MEASURE:
                        setStateMachine(MEASURE, ENTRY);
                    break;
                        
                    case MENU_DATE:
                        setStateMachine(DATE, ENTRY);
                    break;
                }

            default:
                break;
            }

            break;

        case WBGT:

            switch (getAction()) {
            case ENTRY:
                Serial.println("WBGT ENTRY");
                displayWBGTInit();
                setStateMachine(WBGT, DO);
                break;

            case DO:
                Serial.println("WBGT DO");
                if(m_flag_btnB_is_pressed == true) {
                    setStateMachine(WBGT, EXIT);
                    setBtnAllFlgFalse();
                }
                delay(1000);
                displayTempHumiIndex();
                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                setFocusState(MENU_WBGT);
                Serial.println("WBGT EXIT");
                break;

            default:
                break;
            }

            break;

        case MUSIC_STOP:
            switch (getAction()) {
            case ENTRY:
                Serial.println("MUSIC_STOP ENTRY");
                displayMusicInit();
                setStateMachine(MUSIC_STOP, DO);
                break;

            case DO:
                Serial.println("MUSIC_STOP DO");
                if(m_flag_btnA_is_pressed || m_flag_btnB_is_pressed){
                    setStateMachine(MUSIC_STOP, EXIT);
                }
                else if(m_flag_btnC_is_pressed == true) {
                    displayNextMusic();
                    setBtnAllFlgFalse();
                }
                break;

            case EXIT:
                Serial.println("MUSIC_STOP EXIT");
                if(m_flag_btnA_is_pressed == true){
                    setStateMachine(MUSIC_PLAY, ENTRY);
                    setBtnAllFlgFalse();

                }
                else if(m_flag_btnB_is_pressed == true) {
                    setStateMachine(MENU, ENTRY);
                    setBtnAllFlgFalse();
                    setFocusState(MENU_WBGT);
                }
                break;

            default:
                break;
            }

            break;

        case MUSIC_PLAY:

            switch (getAction()) {
            case ENTRY:
                Serial.println("MUSIC_PLAY ENTRY");
                displayMusicPlay();
                mmplay.prepareMP3();
                setStateMachine(MUSIC_PLAY, DO);
                play_flg = true;
                break;

            case DO:
                Serial.println("MUSIC_PLAY DO");
                while(play_flg){
                    play_flg = mmplay.playMP3();

                    if(m_flag_btnA_is_pressed){
                        setBtnAllFlgFalse();
                        break;
                    }
                }

                setStateMachine(MUSIC_PLAY, EXIT);
                mmplay.stopMP3();

                break;

            case EXIT:
                Serial.println("MUSIC_PLAY EXIT");
                setStateMachine(MUSIC_STOP, ENTRY);
                break;

            default:
                break;
            }

            break;

        case MEASURE:

            switch (getAction()) {
            case ENTRY:
                Serial.println("MEASURE ENTRY");
                displayMeasureInit();
                setStateMachine(MEASURE, DO);
                break;

            case DO:
                Serial.println("MEASURE DO");
                if(m_flag_btnB_is_pressed == true) {
                    setStateMachine(MEASURE, EXIT);
                    setBtnAllFlgFalse();
                }
                delay(250);
                displayMeasureDistance();
                break;

            case EXIT:
                Serial.println("MEASURE EXIT");
                setStateMachine(MENU, ENTRY);
                setFocusState(MENU_WBGT);
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction()) {
            case ENTRY:
                Serial.println("DATE ENTRY");
                displayDateInit();
                setStateMachine(DATE, DO);
                break;

            case DO:
                Serial.println("DATE DO");
                if(m_flag_btnB_is_pressed == true) {
                    setStateMachine(DATE, EXIT);
                    setBtnAllFlgFalse();
                }
                delay(100);
                displayDateUpdate();
                break;

            case EXIT:
                Serial.println("DATE EXIT");
                setStateMachine(MENU, ENTRY);
                setFocusState(MENU_WBGT);
                break;

            default:
                break;
            }

        default:
            break;
        }
    }
}
