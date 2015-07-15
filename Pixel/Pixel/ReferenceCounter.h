
#ifndef ReferenceCounter_h
#define ReferenceCounter_h

#include <Pixel\CompileSettings.h>
#include <Pixel\Utils.h>

namespace Pixel
{

	class PIXEL_API ReferenceCounter
	{
	public:
		ReferenceCounter() :
		  m_Count(0)
		  {
		  }

		  void addRef()
		  {
			  ++m_Count;
		  }
		  void release()
		  {
			  if (--m_Count <= 0)
			  {
				  delete this;
			  }
		  }
		  int getReferenceCount()
		  {
			  return m_Count;
		  }
		  //protected:
		  virtual ~ReferenceCounter(){}
	private:
		int m_Count;
	};

}

#endif //ReferenceCounter_h
