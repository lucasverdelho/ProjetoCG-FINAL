#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
#include <iostream>


class Camera{

private:
    double posX,posY,posZ;
    double lookAtX,lookAtY,lookAtZ;
    double upX,upY,upZ;
    double fov,near,far;

public:
    Camera(){
        posX=0,posY=0,posZ=0;
        lookAtX=0,lookAtY=0,lookAtZ=0;
        upX=0,upY=0,upZ=0;
        fov=0,near=0,far=0;
    }


    double getPosX();
    double getPosY();
    double getPosZ();
    double getLookAtX();
    double getLookAtY();
    double getLookAtZ();
    double getUpX();
    double getUpY();
    double getUpZ();
    double getFov();
    double getNear();
    double getFar();

    void setPosX(double posX);
    void setPosY(double posY);
    void setPosZ(double posZ);
    void setLookAtX(double lookAtX);
    void setLookAtY(double lookAtY);
    void setLookAtZ(double lookAtZ);
    void setUpX(double upX);
    void setUpY(double upY);
    void setUpZ(double upZ);
    void setFov(double fov);
    void setNear(double near);
    void setFar(double far);

};


#endif
