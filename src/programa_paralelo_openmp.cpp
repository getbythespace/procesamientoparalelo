#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <omp.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <ImagenEntrada> <ImagenSalida>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    cv::Mat image = cv::imread(inputFile, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error al abrir la imagen: " << inputFile << "\n";
        return 1;
    }

    cv::Mat grayImage(image.size(), CV_8UC1);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            const cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            unsigned char gray = static_cast<unsigned char>(
                pixel[2] * 0.299 + pixel[1] * 0.587 + pixel[0] * 0.114);
            grayImage.at<unsigned char>(i, j) = gray;
        }
    }

    if (!cv::imwrite(outputFile, grayImage)) {
        std::cerr << "Error al guardar la imagen: " << outputFile << "\n";
        return 1;
    }

    return 0;
}

