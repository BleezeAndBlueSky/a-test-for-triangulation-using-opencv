1. edge detection
2. hough transform
3. entropy and scale based
4. corner detection
5. blob detection
6. thresholding
7. template matching
:. ::


在双目视觉中,同一个特征对于两个相机应该是相同或者近似的, 但是由于视角不同,形状会发生扭曲,
虽然可以skew可以透视变幻但我相信不是那么容易的事情,尤其是对于实时的检测.以这里暂时以检测圆为例.

流程大致如下:

        灰度化-> 图像分割(可能需要二值化) -> findcontours-> 提取中心(或重心) ->triangulation
        
要创造一些边界条件减少误识别
        
预计两天内完成
