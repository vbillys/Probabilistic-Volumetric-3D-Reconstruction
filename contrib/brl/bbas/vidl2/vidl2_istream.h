// This is brl/bbas/vidl2/vidl2_istream.h
#ifndef vidl2_istream_h_
#define vidl2_istream_h_
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma interface
#endif
//:
// \file
// \brief A base class for input video streams
//
// \author Matt Leotta
// \date 19 Dec 2005

#include <vil/vil_image_resource_sptr.h>


//: A base class for input video streams
class vidl2_istream
{
 public:
  //: Constructor
  vidl2_istream() {}
  //: Destructor
  virtual ~vidl2_istream() {}

  //: Return true if the stream is open for reading
  virtual bool is_open() const = 0;

  //: Return true if the stream is in a valid state
  virtual bool is_valid() const = 0;

  //: Return true if the stream support seeking
  virtual bool is_seekable() const = 0;

  //: Return the current frame number
  virtual unsigned int frame_number() const = 0;

  //: Close the stream
  virtual void close() = 0;

  //: Advance to the next frame (but don't acquire an image)
  virtual bool advance() = 0 ;

  //: Read the next frame from the stream (advance and acquire)
  virtual vil_image_resource_sptr read_frame() = 0;

  //: Return the current frame in the stream
  virtual vil_image_resource_sptr current_frame() = 0;

  //: Seek to the given frame number
  // \returns true if successful
  virtual bool seek_frame(unsigned int frame_number) = 0;
};

#endif // vidl2_istream_h_
