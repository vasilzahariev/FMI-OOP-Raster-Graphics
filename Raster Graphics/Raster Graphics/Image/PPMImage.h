#pragma once

#include "Image.h"
#include "../ImageData/RGBData.h"

class PPMImage : public Image {
public:
	PPMImage(std::string_view fileName);
	PPMImage(const PPMImage& other);

	PPMImage* clone() override;

	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;

	void rotate(std::string direction) override;

	void grayscale() override;
	void monochrome() override;
	void negative() override;

private:
	Matrix<RGBData> m_pixels;

	void readRowsAndColsFromFileAndResizePixels(std::ifstream& file) override;

	void writeRowsAndColsToFile(std::ofstream& file) const override;

	void copy(Image* image) override;
};
