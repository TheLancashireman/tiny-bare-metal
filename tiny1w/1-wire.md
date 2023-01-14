# Maxim one-wire protocol (e.g. DS18B20)

* Communication always controlled by master.
* Bus is pulled to 0 by communication (open collector).
* Pull-up of 5K0 (4K7) needed

## Reset pulse
* Master pulls low for minimum 480 us, then release.
* Slaves (if present) pull low within 60 us of release for min 60 us, max 240 us

## Write (master --> slave)
* Master pulls low
* Slave samples line between 15 us and 60 us after falling edge. Therefore:
  * To write 0, master holds low for > 60 us (max 120 us)
  * To write 1, master releases after 1 us and waits for > 59 us

## Read (master <-- slave)
* Master pulls low for 1 us
* Read 0: slave holds low between 15 us and 60 us
* Read 1: slave doesn't pull low
* Master samples bus max 15 us after falling edge
* "Read slots must be min 60 us + 1 us recovery time"
