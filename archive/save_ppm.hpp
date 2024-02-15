#include <fstream>
#include <iostream>
#include <vector>
#include <Eigen/Eigen>

namespace RayTracer {
    using color = Eigen::Vector3d;

    int save_ppm(std::string file_name, const std::vector<color>& buffer, int dimx, int dimy) {
        
        std::ofstream ofs(file_name, std::ios_base::out | std::ios_base::binary);
        ofs << "P6" << std::endl << dimx << ' ' << dimy << std::endl << "255" << std::endl;
    
        for (unsigned int j = 0; j < dimy; ++j) {
            std::clog << "\rScanlines remaining: " << dimy-j << ' ' << std::flush;
            for (unsigned int i = 0; i < dimx; ++i) {
                color pixel = buffer[j*dimx+i];
                ofs << (char) (255.0 * pixel.x()) <<  (char) (255.0 * pixel.y()) << (char) (255.0 * pixel.z());
            }
        }

        std::clog << "\rScanlines remaining: 0\nDone!" << std::endl;
        ofs.close();
    
        return 0;

    }
} // namespace RayTracer