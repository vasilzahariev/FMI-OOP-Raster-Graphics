#include "../Image.h"

void Image::undo() {
	if (m_previousVersion == nullptr)
		throw CommandException("Undo command unavailable");

	copy(m_previousVersion);
}

void Image::removeUnsavedChanges() {
	clearPreviousVersions();
}

void Image::setMagicNumber(const std::uint16_t magicNumber) {
	m_magicNumber = magicNumber;
}

std::uint16_t Image::getMagicNumber() const {
	return m_magicNumber;
}

void Image::setMaxColorValue(const std::uint16_t maxColorValue) {
	m_maxColorValue = maxColorValue;
}

std::uint16_t Image::getMaxColorValue() const {
	return m_maxColorValue;
}

Image::Image(std::string_view fileName, const bool grayscale, const bool monochrome, const std::uint16_t maxColorValue)
	: m_fileName(fileName), bGrayscale(grayscale),
	  bMonochrome(monochrome), m_maxColorValue(maxColorValue),
	  m_previousVersion(nullptr) {
}

Image::Image(const Image& other)
	: m_fileName(other.m_fileName), m_magicNumber(other.m_magicNumber),
	  m_maxColorValue(other.m_magicNumber), bGrayscale(other.bGrayscale),
	  bMonochrome(bMonochrome), m_previousVersion(other.m_previousVersion) {
}

Image::~Image() {
	clearPreviousVersions();
}

std::string Image::getFileName() const {
	return m_fileName;
}

bool Image::isGrayscale() const {
	return bGrayscale;
}

bool Image::isMonochrome() const {
	return bMonochrome;
}

void Image::readMagicNumberFromFile(std::ifstream& file) {
	file.ignore();
	file >> m_magicNumber;
}

void Image::readMaxColorValueFromFile(std::ifstream& file) {
	file >> m_maxColorValue;
}

void Image::writeMagicNumberToFile(std::ofstream& file) const {
	file << 'P' << m_magicNumber << '\n';
}

void Image::writeMaxColorValue(std::ofstream& file) const {
	file << m_maxColorValue << '\n';
}

void Image::clearPreviousVersions() {
	if (m_previousVersion == nullptr) return;

	m_previousVersion->clearPreviousVersions();

	delete m_previousVersion;
	m_previousVersion = nullptr;
}

void Image::copy(Image* image) {
	m_fileName = image->m_fileName;
	m_magicNumber = image->m_magicNumber;
	m_maxColorValue = image->m_maxColorValue;
	bGrayscale = image->bGrayscale;
	bMonochrome = image->bMonochrome;
	m_previousVersion = image->m_previousVersion;

	delete image;
}
