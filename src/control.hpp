#ifndef CONTROL_HPP
#define CONTROL_HPP

class Controller {
	public:
		int Init(int);
		void Reset(int);
		void Pause(int);
		void CloseDown(void);
		bool HasShaker(void);
		bool IsConnected(void);
		void Update(void);
		void StartRecord(ControllerRecordEntry *, u32, u32 *);
		void StartPlay(ControllerRecordEntry *, u32);
		void PlayShake(char *, int);
		void StartShake(char *, int);
		void Vibrate(int, int);
		void Jolt(int, int);
		void Push(int, int);
		void SetFriction(float);
		void ClearKeys(void);

		u32 _000[0x84 / 4];
}; // size: 0x84

#endif
