#ifndef Point_h
#define Point_h

class Point {


private:
    float x;
    float y;
    float z;
    float normalX;
    float normalY;
    float normalZ;
    float textX;
    float textY;


public:

	Point();

	Point(float x, float y, float z);

    Point(float x, float y, float z,float normalX, float normalY, float normalZ, float textX, float textY);

	Point(const Point& p);

	float getX();

	float getY();

	float getZ();

    float getNormalX() const;

    float getNormalY() const;

    float getNormalZ() const;

    float getTextX() const;

    float getTextY() const;

    ~Point();

};


#endif 