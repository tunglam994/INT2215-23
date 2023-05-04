
#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();

	bool is_started();
	bool is_paused();


private:
	int start_tick_;
	int paused_tick_;

	bool is_paused_;
	bool is_started_;

};

#endif // !IMP_TIMER_H_
