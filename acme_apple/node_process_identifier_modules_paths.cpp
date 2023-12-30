//
//  node_process_identifier_modules_paths.cpp
//  acme_darwin
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 11/11/23 18:26
//  <3ThomasBorregaardSorensen!!
//
//https://stackoverflow.com/questions/4309117/determining-programmatically-what-modules-are-loaded-in-another-process-os-x
#include "framework.h"


#include <stdio.h>
#include <stdlib.h>
#if defined(__APPLE__)
#include <mach-o/dyld_images.h>
#include <mach/vm_map.h>
#endif

//#define PATH_MAX 2048


// to build.
// cc  -o test_mach test_mach.c

// Helper function to read process memory (a la Win32 API of same name) To make
// it easier for inclusion elsewhere, it takes a pid, and does the task_for_pid
// by itself. Given that iOS invalidates task ports after use, it's actually a
// good idea, since we'd need to reget anyway

unsigned char *
readProcessMemory (int pid,
        mach_vm_address_t addr,
        mach_msg_type_number_t* size) {
    task_t t;
    task_for_pid(mach_task_self(), pid, &t);
    mach_msg_type_number_t  dataCnt = (mach_msg_type_number_t) *size;
    vm_offset_t readMem;

    // Use vm_read, rather than mach_vm_read, since the latter is different in
    // iOS.

        kern_return_t kr = vm_read(t,           // vm_map_t target_task,
                     addr,                      // mach_vm_address_t address,
                     *size,                     // mach_vm_size_t size
                     &readMem,                  //vm_offset_t *data,
                     &dataCnt);                 // mach_msg_type_number_t *dataCnt

        if (kr) {
            fprintf (stderr, "Unable to read target task's memory @%p - kr 0x%x\n" ,
                    (void *) addr, kr);
             return NULL;
        }

    return ( (unsigned char *) readMem);
}


int apple_node_process_identifier_modules_paths(int pid, void * p, void (*callback)(void *, const char *, int ))
{

    task_t task;
    auto ret = task_for_pid(mach_task_self(),pid, &task);
   
   if(ret != KERN_SUCCESS)
   {
      
   
      
      return ret;
      
   }

    struct task_dyld_info dyld_info;
    mach_msg_type_number_t count = TASK_DYLD_INFO_COUNT;

   ret = task_info(task, TASK_DYLD_INFO, (task_info_t) &dyld_info, &count);
   
   if(ret != KERN_SUCCESS)
   {
      
      return ret;
      
   }
        mach_msg_type_number_t size = sizeof(struct dyld_all_image_infos);

        uint8_t* data =
            readProcessMemory(pid, dyld_info.all_image_info_addr, &size);
        struct dyld_all_image_infos* infos = (struct dyld_all_image_infos *) data;

        mach_msg_type_number_t size2 =
            sizeof(struct dyld_image_info) * infos->infoArrayCount;
        uint8_t* info_addr =
            readProcessMemory(pid, (mach_vm_address_t) infos->infoArray, &size2);
        struct dyld_image_info* info = (struct dyld_image_info*) info_addr;

        for (int i=0; i < infos->infoArrayCount; i++) {
            mach_msg_type_number_t size3 = PATH_MAX;

            uint8_t* fpath_addr = readProcessMemory(pid,
                    (mach_vm_address_t) info[i].imageFilePath, &size3);
            if (fpath_addr)
            {
             //  printf("path: %s %d\n",fpath_addr , size3);
               callback(p, (const char *) fpath_addr, size3);
            }
        }
    
    return ret;
}
