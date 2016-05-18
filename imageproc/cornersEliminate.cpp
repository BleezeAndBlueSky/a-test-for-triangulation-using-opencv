// use cornerHarris fun to detect corners, then eliminate them
// completely nosense work, just for recording

    cv::Mat cornerContainer;
    cv::cornerHarris(roi_enlarged,cornerContainer,7,7,0.05);
    //the dst of cornerHarris is CV_32FC1, so the pixel value type is float
    cv::threshold(cornerContainer,cornerContainer,0.001, 255,cv::THRESH_BINARY);
    if(debugflag)
        cv::imshow("corner",cornerContainer);
/*
    ////   Alternative Method for Mat iteration
    for(int i=0; i<cornerContainer.rows; ++i)
        for(int j=0; j<cornerContainer.cols; ++j)
            if(cornerContainer.at<float>(i,j) != 0)
                roi_enlarged.at<uchar>(i,j) = 0;
*/
    // set corner section to zero
    cv::MatIterator_<float> itHarris;
    cv::MatIterator_<uchar> itsrc;
    itHarris = cornerContainer.begin<float>();
    for(;itHarris != cornerContainer.end<float>(); ++itHarris)
        if(*itHarris != 0){
            itsrc = itHarris - cornerContainer.begin<float>() + roi_enlarged.begin<uchar>();
            *itsrc = 0;
        }
    if(debugflag)
        cv::imshow("After corner eliminate",roi_enlarged);
