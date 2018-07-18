
#include <cstdint>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

typedef bool (*CallbackOnEvent)(int keypress);

extern "C" {
  void* CvRaster_getData(uint64_t native);
  uint64_t CvRaster_copy(uint64_t native);
  uint64_t CvRaster_makeMatFromRawDataReference(uint32_t rows, uint32_t cols, uint32_t type, uint64_t dataLong);
  uint64_t CvRaster_defaultMat();
  void CvRaster_showImage(const char* name, uint64_t native, CallbackOnEvent callback, int32_t millisToSleep);
  void CvRaster_updateWindow(const char* name, long native);
}

void* CvRaster_getData(uint64_t native) {
  cv::Mat* mat = (cv::Mat*) native;

  if (!mat->isContinuous())
    return NULL;

  return mat->ptr(0);
}

uint64_t CvRaster_copy(uint64_t native) {
  cv::Mat* mat = (cv::Mat*) native;

  if (!mat->isContinuous())
    return 0L;

  cv::Mat* newMat = new cv::Mat((*mat));
  return (uint64_t) newMat;
}

uint64_t CvRaster_makeMatFromRawDataReference(uint32_t rows, uint32_t cols, uint32_t type, uint64_t dataLong) {
  void* data = (void*) dataLong;
  cv::Mat* newMat = new cv::Mat(rows, cols, type, data);

  return (uint64_t) newMat;
}

uint64_t CvRaster_defaultMat() {
  cv::Mat* ret = new cv::Mat();
  return (uint64_t) ret;
}

void CvRaster_showImage(const char* name, uint64_t native, CallbackOnEvent callback, int32_t millisToSleep) {
	  cv::Mat* mat = (cv::Mat*) native;
	  cv::String sname(name);
	  cv::namedWindow(sname);
	  cv::imshow(sname,*mat);
	  for (bool done = false; !done;) {
		  int key = cv::waitKey(millisToSleep);
		  done = callback ? (*callback)(key) : true;
	  }
	  cv::destroyWindow(sname);
}

void CvRaster_updateWindow(const char* name, long native) {
	  cv::Mat* mat = (cv::Mat*) native;
	  cv::String sname(name);
	  cv::imshow(sname,*mat);
}

