#include"DeMultiPlex.h"
#include"DeMultiPlexEpoll.h"

namespace Net
{

      DeMultiPlex* DeMultiPlex::create(EventLoop * loop)
	  {
	     return DeMultiplexEpoll(loop);
	  }
     
};


#endif
