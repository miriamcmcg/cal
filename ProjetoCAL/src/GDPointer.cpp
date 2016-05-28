#include "GDPointer.h"



GDPointer::GDPointer(GarbageDeposit *gd){
	gd_ptr = gd;
};

GarbageDeposit *GDPointer::getPointer() const {
	return gd_ptr;
}

bool GDPointer::operator==(const GDPointer &gd) const {
	return *gd_ptr == *gd.gd_ptr;
}

bool GDPointer::operator!=(const GDPointer &gd) const {
	return !(*gd_ptr == *gd.gd_ptr);
}

void GDPointer::setPosition(const GDPointer &gd1, const GDPointer &gd2) {
	gd_ptr->setX( (gd1.getPointer()->getX() + gd2.getPointer()->getX() ) / 2);
	gd_ptr->setY( (gd1.getPointer()->getY() + gd2.getPointer()->getY() ) / 2);
	gd_ptr->setZ( (gd1.getPointer()->getZ() + gd2.getPointer()->getZ() ) / 2);
}
