package com.albert.study.myapplication;

public interface AudioRecordListener {
    /**
     * 获取录制音量的大小
     *
     * @param volume
     */
    void onGetVolume(int volume);
}
