package org.cocos2dx.cpp; 
  
import java.io.File;  
import java.io.IOException;
  
import android.media.MediaRecorder;  
import android.os.Handler;  
import android.util.Log;  
import android.widget.ImageView; 

public class JniRecorder {
	private final String TAG = "JniRecord";
	private MediaRecorder mMediaRecorder;
	private static JniRecorder jniRecorder;// = new JniRecorder();
	public static final int MAX_LENGTH = 1000 * 60 * 10;
	private File file; 
	 
	private long startTime;  
	private long endTime;  
	private boolean isRecord;
	private int counter = 0;
	 
	static public synchronized JniRecorder getInstance(){
		if(jniRecorder == null){
			jniRecorder = new JniRecorder();
			jniRecorder.isRecord = false;
		}
		return jniRecorder;
	}
	 
	static public int jniStartRecord(){
		return getInstance().startRecord();
	}
	 
	static public int jniStopRecord(){
		if(jniRecorder == null){
			return -11;
		}
		return jniRecorder.stopRecord();
	}
	 
	static public int jniGetVol(int max){
		if(jniRecorder == null){
			return -111110;
		}
		return jniRecorder.updateMicStatus();
		//return jniRecorder.testUpdate();
	}

	public int startRecord() {
		if (isRecord){
			return -22;
		}
		if (mMediaRecorder != null){
			return -222;
		}
		if (mMediaRecorder == null){
			mMediaRecorder = new MediaRecorder();
			try {
				mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
				mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.RAW_AMR);
				mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
				mMediaRecorder.setOutputFile("/storage/emulated/0/Download/ase.amr");
				//mMediaRecorder.setOutputFile("/sdcard/Download/ase.amr");
				mMediaRecorder.setMaxDuration(MAX_LENGTH);
			} catch (IllegalStateException e) {
				mMediaRecorder.reset();
				mMediaRecorder.release();
				mMediaRecorder = null;
				return -22200;
			}
			try {
				mMediaRecorder.prepare();
			} catch (IllegalStateException e) { 
				Log.i(TAG,  "call startAmr(File mRecAudioFile) failed!" + e.getMessage());
				mMediaRecorder.reset();
				mMediaRecorder.stop();
				mMediaRecorder.release();
				mMediaRecorder = null;
				return -22211;
			} catch (IOException e) {
				Log.i(TAG,  "call startAmr(File mRecAudioFile) failed!" + e.getMessage());
				mMediaRecorder.stop();
				mMediaRecorder.reset();
				mMediaRecorder.release();
				mMediaRecorder = null;
				return -22212;
			}
			try {
				mMediaRecorder.start();
			} catch (IllegalStateException e) { 
				Log.i(TAG,  "call startAmr(File mRecAudioFile) failed!" + e.getMessage());
				mMediaRecorder.reset();
				mMediaRecorder.stop();
				mMediaRecorder.release();
				mMediaRecorder = null;
				return -22221;
			}
			//AudioRecord audioRecord.
			//startTime = System.currentTimeMillis();
			//updateMicStatus();
			Log.i("ACTION_START", "startTime" + startTime);
			isRecord = true;
			counter = 0;
			return mMediaRecorder.getMaxAmplitude();
			//return 1;
		}
		return -2222;
	}  
	 
	public int stopRecord() {
	    if (mMediaRecorder == null)  {
			counter = 0;
	        return -200;
		}
		if (isRecord == false){
			counter = 0;
			//return -20;
		}
	    //endTime = System.currentTimeMillis();
        Log.i("ACTION_END", "endTime" + endTime);
		try {
			mMediaRecorder.stop();
		} catch (IllegalStateException e) { 
			mMediaRecorder.reset();
			mMediaRecorder.release();
			mMediaRecorder = null;
			return -2001;
		}
		mMediaRecorder.reset();
		mMediaRecorder.release();
		mMediaRecorder = null;
		Log.i("ACTION_LENGTH", "Time" + (endTime - startTime));
		isRecord = false;
		counter = 0;
		//return endTime - startTime;
		return 11;
	};
	
	/*
	private final Handler mHandler = new Handler();
	private Runnable mUpdateMicStatusTimer = new Runnable() {
	public void run() {
		updateMicStatus();
	}
	*/
	private int BASE = 600;
	private int SPACE = 200;
	
	private int updateMicStatus() {
		if (mMediaRecorder != null) {
	        int vuSize = 10 * mMediaRecorder.getMaxAmplitude() / 32768;
			int ratio = mMediaRecorder.getMaxAmplitude() / BASE;
	        int db = 0;
			if (ratio > 1)
	            db = (int) (20 * Math.log10(ratio));
				System.out.println("microPhone"+db+" "+Math.log10(ratio));
				//mHandler.postDelayed(mUpdateMicStatusTimer, SPACE);
           
			if (db > 1) {
				vuSize = (int) (20 * Math.log10(db));
				Log.i("mic_", "Vol" + vuSize);
			}
			else
			{
				Log.i("mic_", "Vol" + 0);
			}
			//return db;
			//return ratio;
			//return vuSize;
			return mMediaRecorder.getMaxAmplitude();
		}
		return -2220;
	}

	private int testUpdate(){
		return counter ++;
	}
}
