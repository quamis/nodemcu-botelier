# nodemcu-botelier

Transform you NodeMcu device into a sort of _butler_, taking commands from a master, and executing them in order.

Name comes from https://en.wikipedia.org/wiki/Butler

The dev plan:
---
	- connect to local wifi
    - connect to master, getCommands
    - execute commands
    - send responses
	

Possible requests:
----
    [x] heartbeat
    [ ] list temperatures
    [ ] list triggers
    [ ] list lights
    [x] list wifi's
    [ ] getStatus (internal status)
        - IP
        - uptime
        - command counts
        - free memory
    [ ] setStatus? (internal status)
    [ ] trigger (1,2,3)
    [x] sleep X secs
    [ ] reboot
    [ ] watchdog for main server
        - arm
        - rearm
        - disarm
    [ ] flush queue
    
    
----
My used pins:

    [3p] senzor lumina 
        - 1 senzor in strada
        - 1 sensor in parcare 
        - 1 senzor in living
    [3p] triggers (relee)
        - bec afara
        - router
        - BPI (watchdog)
        
    [1p] temperatures
    [1p] senzor usa
    [1p] interrupt for wakeup
     =9p ... cam multi:)
    