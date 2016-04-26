#include "GDPointer.h"



GDPointer::GDPointer(GarbageDeposit *gd){
	gd_ptr = gd;
};

GarbageDeposit *GDPointer::getPointer(){
	return gd_ptr;
}

bool GDPointer::operator==(const GDPointer &gd) const {
	return *gd_ptr == *gd.gd_ptr;
}

bool GDPointer::operator!=(const GDPointer &gd) const {
	return !(*gd_ptr == *gd.gd_ptr);
}
