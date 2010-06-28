package de.bloodyblades.ms3dloader;



import org.lwjgl.Sys;


/**
 * Timer class using a combination of the Java nano timer and the LWJGL timer
 * 
 * @author xindon
 */
public class Timer {

	private long lastTime;


	/***************************************************************************************************************************************************************************************************
	 * Timer() - Constructor
	 **************************************************************************************************************************************************************************************************/
	public Timer() {

		resetTimer();
	}


	/***************************************************************************************************************************************************************************************************
	 * resetTimer() - Reset the timer to the current time
	 **************************************************************************************************************************************************************************************************/
	public void resetTimer() {

		this.lastTime = java.lang.System.nanoTime();
	}


	/***************************************************************************************************************************************************************************************************
	 * getElapsedMillis() - Get the elapsed time since last timer reset in milliseconds
	 **************************************************************************************************************************************************************************************************/
	public double getElapsedMillis() {

		return (this.getElapsedNanos() / 1000.0) *  1.0 / Sys.getTimerResolution();
	}


	/***************************************************************************************************************************************************************************************************
	 * getElapsedTicks() - Get the elapsed ticks since last timer reset
	 **************************************************************************************************************************************************************************************************/
	public long getElapsedNanos() {

		return (java.lang.System.nanoTime() - this.lastTime);
	}
}
