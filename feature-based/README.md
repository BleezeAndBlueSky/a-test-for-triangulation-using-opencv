1. edge detection
2. hough transform
3. entropy and scale based
4. corner detection
5. blob detection
6. thresholding
7. template matching
8. sift / surf

:  :


在双目视觉中,同一个特征对于两个相机应该是相同或者近似的, 但是由于视角不同,形状会发生扭曲,
虽然可以skew可以透视变幻但我相信不是那么容易的事情,尤其是对于实时的检测.以这里暂时以检测圆为例.

流程大致如下:

        灰度化-> 图像分割(可能需要二值化) -> findcontours-> 提取中心(或重心) ->triangulation
        
要创造一些边界条件减少误识别
        
预计两天内完成


另外,目前据我了解,检测中很少使用被动视觉, 应该说没有见过相关的论文, 大三实习中只见过电路板的识别,
好像是双目记不太清,貌似是用的模板匹配.

这里说话不太严密, 刚刚看到一篇论文基于被动视觉检测焊接过程.. 其实我想表达的是, 特征不容易提取
需要人为的去制造特征,比如激光,结构光,Kinect那种编码光, 某些机器视觉检测系统用的标定块,这是我理解的
主动视觉

至于用sift或surf匹配这样的被动视觉, 我并不了解,autodesk123D好像用的就是这玩意, 精度方面会很好吗?
工业界认可吗?

检测一般使用激光或者结构光,好像不太符合基于特征的主题,基于特征然后再配合结构光效果可能更好
所以再写一个模板匹配的例子,模板匹配和轮廓检测在opencv里都有样例,不好抄袭,所以可能也就修改下程序

嘛~借这个机会就好好学学模板匹配吧~

预计四天内完成