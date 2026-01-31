#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int main()
{
    const int width = 256;
    const int height = 256;

    const string outPath = string(PROJECT_ROOT_DIR) + "/build/bin/Release/output/preview.ppm";


    ofstream out(outPath, ios::out | ios::trunc);
    if (!out)
    {
        cerr << "Error opening output file " << outPath << endl;
        return 1;
    }

    out << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j = height -1; j >= 0; --j)
    {
        for (int i = 0; i < width; ++i)
        {
            //simple gradient
            const int r = static_cast<int>(255.0 * i / (width - 1));
            const int g = static_cast<int>(255.0 * j / (height - 1));
            const int b = 64;
            out << r << ' ' << g << ' ' << b << '\n';
        }
    }
    cout << "Wrote " << outPath << "\n";
    return 0;
}