Item lists

两个摄像头,  第一眼，     两个淘宝20包邮，              很不好用
点、线、十字激光，        淘宝一元到十几元不等              亮了

联想笔记本T6600，3GB ddr3，仅有两个usb接口                       由于同一host usb带宽不足，两个摄像头不能同时使用（xp与ubuntu）
945台式机 E2180，2GB ddr2                                        卡顿严重，单摄像头同样卡顿严重（在xp和ubuntu都严重卡顿）

手里有个八、九年前的十元摄像头，很流畅，问题应该是出在摄像头，试过和新的混合使用，成像上差太多没有继续
试遍了谷歌前四页所提的方法，甚至试图去改驱动源码（没编译成功），不如买对新的更方便些，但是时间有限，没有继续下去
关键字：libv4l2: error turning on stream: No space left on device 
        VIDIOC_STREAMON: No space left on device 

台式机
tau@tau-MS-7236:~$ lsusb -t
/:  Bus 04.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M
/:  Bus 03.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M
    |__ Port 1: Dev 2, If 0, Class=Video, Driver=uvcvideo, 12M
    |__ Port 1: Dev 2, If 1, Class=Video, Driver=uvcvideo, 12M
    |__ Port 1: Dev 2, If 2, Class=Audio, Driver=snd-usb-audio, 12M
    |__ Port 1: Dev 2, If 3, Class=Audio, Driver=snd-usb-audio, 12M
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M
    |__ Port 1: Dev 2, If 0, Class=Video, Driver=uvcvideo, 12M
    |__ Port 1: Dev 2, If 1, Class=Video, Driver=uvcvideo, 12M
    |__ Port 1: Dev 2, If 2, Class=Audio, Driver=snd-usb-audio, 12M
    |__ Port 1: Dev 2, If 3, Class=Audio, Driver=snd-usb-audio, 12M
笔记本
tau@tau:~/Documents/kernel-git$ lsusb -t
/:  Bus 08.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M 
/:  Bus 07.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M 
/:  Bus 06.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M 
/:  Bus 05.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M 
/:  Bus 04.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M 
/:  Bus 03.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M 
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/6p, 480M 
    |__ Port 1: Dev 5, If 0, Class=Video, Driver=uvcvideo, 480M 
    |__ Port 1: Dev 5, If 1, Class=Video, Driver=uvcvideo, 480M 
    |__ Port 1: Dev 5, If 2, Class=Audio, Driver=snd-usb-audio, 480M 
    |__ Port 1: Dev 5, If 3, Class=Audio, Driver=snd-usb-audio, 480M 
    |__ Port 3: Dev 3, If 0, Class=Video, Driver=uvcvideo, 480M 
    |__ Port 3: Dev 3, If 1, Class=Video, Driver=uvcvideo, 480M 
    |__ Port 3: Dev 3, If 2, Class=Audio, Driver=snd-usb-audio, 480M 
    |__ Port 3: Dev 3, If 3, Class=Audio, Driver=snd-usb-audio, 480M 
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/6p, 480M 
