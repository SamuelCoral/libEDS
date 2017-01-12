


#ifndef __EXCEPCION_EDS_HPP__
#define __EXCEPCION_EDS_HPP__


#include <exception>
#include <string>


namespace eds
{
	class excepcion_eds : std::exception
	{
		
	protected:
		
		std::string mensaje;
		
	public:
		
		excepcion_eds(std::string mensaje) : mensaje(mensaje) {  }
		inline const char* what() { return mensaje.c_str(); }
		~excepcion_eds() throw() { mensaje.~basic_string(); }
	};
}


#endif /* __EXCEPCION_EDS_HPP__ */

