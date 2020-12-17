
#ifndef		__ALARM_INTERFACE_H__
#define		__ALARM_INTERFACE_H__



extern	void	Short_circuit_windows(void);
extern	void	Open_circuit_windows(void);
extern	void	Low_ATOMIZER_windows(void);
extern	void	HIGH_ATOMIZER_windows(void);
extern	void	Low_Battery_windows(void);
extern	void	Smoking_timeout_windows(void);
extern	void	PCB_Overheated_windows(void);
extern	void	USB_anomaly_windows(void);
extern	void	(*Warning_Windows)(void);
extern	void	Warning_interface(void);
extern	void	Batt_error_interface(void);
extern	void	FIRE_TO_UNLOCK_windows(void);
extern	void	MODE_TO_SET_windows(void);
extern	void	USB_Warning_interface(void);

#endif
