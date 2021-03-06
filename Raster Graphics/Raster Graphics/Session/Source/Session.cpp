#include "../Session.h"

int Session::sIdCounter = 0;

Session::Session()
	: nId(++sIdCounter) {
}

int Session::getId() const {
	return nId;
}

Session::~Session() {
	close();
}

void Session::grayscale() {
	for (ImageVector::iterator imageIt = m_images.begin(); imageIt != m_images.end(); ++imageIt)
		if (!(*imageIt)->isGrayscale() && !(*imageIt)->isMonochrome())
			(*imageIt)->grayscale();

	m_unsavedChanges.push_back("grayscale");
}

void Session::addImage(Image* image) {
	m_images.push_back(image);
}

void Session::rotate(std::string& direction) {
	for (size_t index = 0; index < m_images.size(); ++index)
		m_images[index]->rotate(direction);

	m_unsavedChanges.push_back("rotate " + direction);
}

void Session::monochrome() {
	for (ImageVector::iterator imageIt = m_images.begin(); imageIt != m_images.end(); ++imageIt)
		if (!(*imageIt)->isMonochrome())
			(*imageIt)->monochrome();

	m_unsavedChanges.push_back("monochrome");
}

void Session::saveChanges() {
	for (ImageVector::iterator imageIt = m_images.begin(); imageIt != m_images.end(); ++imageIt)
		saveImageToFile(*imageIt, (*imageIt)->getFileName());

	m_unsavedChanges.clear();
}

void Session::negative() {
	for (ImageVector::iterator imageIt = m_images.begin(); imageIt != m_images.end(); ++imageIt)
		(*imageIt)->negative();

	m_unsavedChanges.push_back("negative");
}

void Session::saveAs(const std::string& fileName) {
	if (m_images.size() == 0)
		throw SessionException("FATAL: No images in an active session");
	
	saveImageToFile(m_images[0], fileName);

	if (m_images.size() == 1)
		m_unsavedChanges.clear();
}

void Session::close() {
	for (ImageVector::iterator imageIt = m_images.begin(); imageIt != m_images.end(); ++imageIt) {
		(*imageIt)->removeUnsavedChanges();
	}
}

void Session::undo() {
	if (m_unsavedChanges.size() == 0)
		throw CommandException("Undo command unavailable");

	std::string msg = "";

	for (ImageVector::iterator imageIt = m_images.begin(); imageIt != m_images.end(); ++imageIt) {
		try {
			(*imageIt)->undo();

			msg = "";
		}
		catch (const CommandException& err) {
			msg = err.what();
		}
	}

	if (msg != "")
		throw CommandException(msg);

	m_unsavedChanges.pop_back();
}

void Session::saveImageToFile(Image* image, const std::string& fileName) {
	std::ofstream file(fileName);

	if (!file.is_open())
		throw FileException("Couldn't open file");

	image->writeToFile(file);
}

std::string Session::info(std::ostream& out) const {
	std::string infoStr = "";

	infoStr += "Session ID: " + std::to_string(nId) + '\n';

	infoStr += "Names of images in the session: ";
	for (size_t index = 0; index < m_images.size(); ++index)
		infoStr += m_images[index]->getFileName() + ' ';
	infoStr += '\n';

	infoStr += "Pending transformations: ";
	for (std::vector<std::string>::const_iterator unsavedChange = m_unsavedChanges.begin(); unsavedChange != m_unsavedChanges.end(); ++unsavedChange)
		infoStr += *unsavedChange + ' ';
	infoStr += '\n';

	return infoStr;
}

bool Session::containsFile(std::string_view fileLocation) const {
	for (ImageVector::const_iterator imageIt = m_images.cbegin(); imageIt != m_images.cend(); ++imageIt)
		if ((*imageIt)->getFileName() == fileLocation)
			return true;

	return false;
}

bool Session::areThereUnsavedChanges() const {
	return m_unsavedChanges.size() != 0;
}
