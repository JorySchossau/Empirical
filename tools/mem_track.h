#ifndef EMP_MEM_TRACK
#define EMP_MEM_TRACK

//////////////////////////////////////////////////////////////////////////////////////////
//
//  This class creates macros to track how many instances of specific classes are made.
//
//  To setup, every constructor for a class must incude EMP_TRACK_CONSTRUCT(CLASS_NAME),
//  and every destructor must have EMP_TRACK_DESTRUCT(CLASS_NAME).  Make sure to avoid
//  implicit constructors/destructors or counts will be off.
//
//  To collect information, EMP_TRACK_COUNT(CLASS_NAME) will provide the current count
//  for a specific class, and EMP_TRACK_STATUS will translate into a string providing
//  information about all available classes.
//
//  Developer notes:
//   Currently having issues with the memory map getting corrupted.  Perhaps it needs to
//   wait until onload is finished?  Also, can try using JS maps instead?  (only when
//   using Emscripten.
//


#define EMP_NO_MEM_CHECK


// If NDEBUG is turned on, turn off mem checks.
// #ifdef NDEBUG
// #define EMP_NO_MEM_CHECK
// #endif


#include <map>
#include <string>
#include <sstream>

#include "alert.h"

#ifdef EMP_NO_MEM_CHECK

#define EMP_TRACK_CONSTRUCT(CLASS_NAME)
#define EMP_TRACK_DESTRUCT(CLASS_NAME)
#define EMP_TRACK_COUNT(CLASS_NAME) 0
#define EMP_TRACK_STATUS std::string("(not in debug mode)")

#else  // DEBUG MODE!

#define EMP_TRACK_CONSTRUCT(CLASS_NAME) emp::internal::TrackMem_Inc(#CLASS_NAME)
#define EMP_TRACK_DESTRUCT(CLASS_NAME) emp::internal::TrackMem_Dec(#CLASS_NAME)
#define EMP_TRACK_COUNT(CLASS_NAME) emp::internal::TrackMem_Count(#CLASS_NAME)
#define EMP_TRACK_STATUS emp::internal::TrackMem_Status()

namespace emp {

  namespace internal {
    std::map<std::string,int> & TrackMem_GetMap() {
      static std::map<std::string,int> * track_mem_class_map = nullptr;
      if (!track_mem_class_map) track_mem_class_map = new std::map<std::string,int>;
      return *track_mem_class_map;
    }

    std::string TrackMem_Status() {
      auto & mem_map = TrackMem_GetMap();
      return "Test!";
      /*
      std::stringstream ss;
      for (auto stat : mem_map) {
        ss << "[" << stat.first << "] : " << stat.second << std::endl;
      }
      return ss.str();
      */
    }

    void TrackMem_Inc(const std::string & class_name) {
      (void) class_name;
      auto & mem_map = TrackMem_GetMap();
      // std::cerr << "Creating: [" << class_name << "]" << std::endl;
      if (mem_map.find(class_name) == mem_map.end()) {
        emp::CappedAlert(10, "New class: ", class_name, "; Total classes: ", mem_map.size());
        mem_map[class_name] = 0;
      }
      mem_map[class_name]++;
      /*
      */
    }

    void TrackMem_Dec(const std::string & class_name) {
      (void) class_name;
      auto & mem_map = TrackMem_GetMap();
      /*
      // Make sure we are not trying to delete a class that was never registered!
      // std::cerr << "Deleting: [" << class_name << "]" << std::endl;
      // std::cerr << "Deleting." << std::endl;
      if (mem_map.find(class_name) == mem_map.end()) {
        emp::CappedAlert(3, "Trying to delete unknown: [", class_name,
                         "]; map size = ", mem_map.size());

        for (auto stat : mem_map) {
          emp::Alert("[", stat.first, "] : ", stat.second, "  (deleting [", class_name, "]");
        }

        abort();
      }
      mem_map[class_name]--;
      if (mem_map[class_name] < 0) {
        emp::CappedAlert(3, "Trying to delete too many: ", class_name);
        abort();
      }
      */
    }

    int TrackMem_Count(const std::string & class_name) {
      (void) class_name;
      auto & mem_map = TrackMem_GetMap();
      return 0;
      /*
      if (mem_map.find(class_name) == mem_map.end()) {
        return 0;
      }
      return mem_map[class_name];
      */
    }
      
  }

}
#endif


#endif