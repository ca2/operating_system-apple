// From acme/exception/exception.h by camilo on 2022-01-09 05:02 <3ThomasBorregaardSorensen!!
#pragma once



class ns_exception :
   public ::exception
{
public:


   int m_iCode;


   ns_exception();
   ~ns_exception();
   

};



