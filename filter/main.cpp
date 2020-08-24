#include <iostream>
#include <string>
#include "Array.h"
#include "Image.h"
#include "ppm/ppm.h"
#include "FilterLinear.h"
#include "FilterGamma.h"


using namespace imaging;
using namespace math;
using namespace std;

int main(int argc, char *argv[]) {

	Image img = Image();
	string filename, filter;
	float aR, aG, aB, cR, cG, cB, k;
	std::cout << "> filter ";
	vector<string> arguments = vector<string>();

	while (true) {
		if (cin.get() == '\n') {
			break;
		}
		else {
			string input;
			cin >> input;
			arguments.push_back(input);
		}
			
	}

	filename = arguments[arguments.size() - 1];
	std::size_t pos = filename.find(".");
	std::string format = filename.substr(pos + 1);
	bool loading = img.load(filename, format);
	std::cout << "Image dimensions are " << img.getWidth() << " x " << img.getHeight() << std::endl;

	int i = 0;
	while (arguments[i + 1] == "linear" || arguments[i + 1] == "gamma") {
		if (arguments[i + 1] == "linear") {
			aR = strtof((arguments[i + 2]).c_str(), 0);
			aG = strtof((arguments[i + 3]).c_str(), 0);
			aB = strtof((arguments[i + 4]).c_str(), 0);
			cR = strtof((arguments[i + 5]).c_str(), 0);
			cG = strtof((arguments[i + 6]).c_str(), 0);
			cB = strtof((arguments[i + 7]).c_str(), 0);
			Vec3<float> a = Vec3<float>(aR, aG, aB);
			Vec3<float> c = Vec3<float>(cR, cG, cB);
			FilterLinear linear = FilterLinear(a, c);
			if (loading) {
				img = linear << img;
			}

			i = i + 8;
			if (i >= arguments.size() - 1) {
				break;
			}
		}
		else if (arguments[i + 1] == "gamma") {
			k = strtof((arguments[i + 2]).c_str(), 0);
			filename = arguments[arguments.size() - 1];
			FilterGamma gamma = FilterGamma(k);

			if (loading) {
				img = gamma << img;
			}
			i = i + 3;
			if (i >= arguments.size() - 1) {
				break;
			}
		}
		else {
			cout << "This Filter doesn't exist..!!!" << endl;
			system("PAUSE");
			exit(0);
		}
	}
	
	std::string filtered = "filtered_" + filename;
	img.save(filtered, "ppm"); 

	system("PAUSE");
}


