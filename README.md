# nodemcu-botelier

The dev plan:
	- connect to local wifi
    - connect to master, getCommands
    - execute commands from queue
	

The plan:
    - heartbeat
    - list temperatures
    - list triggers
    - list lights
    - list wifi's
    - getStatus (internal status)
        - IP
        - uptime
        - command counts
    - setStatus (internal status)
    - trigger (1,2,3)
    - sleep X secs
    - reboot
    - watchdog
        - arm
        - rearm
        - disarm
    - flush queue
    
    

The pins:
    [3p] sensor lumina 
        - 1 senzor strada
        - 1 sensor parcare vecini
        - 1 senzor in living
    [3p] trigger 
        - bec afara
        - router
        - BPI (watchdog)
        
    [1p] temperatures
    [1p] sensor usa intrare
    [1p] interrupt for wakeup
    =9 ??? cam multi:)
    