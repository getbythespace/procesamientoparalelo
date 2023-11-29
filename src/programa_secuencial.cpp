#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

// Función para convertir una imagen a escala de grises usando el método de luminosidad
void convertToGrayscale(const cv::Mat& input, cv::Mat& output) {
    output = cv::Mat(input.size(), CV_8UC1);

    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            const cv::Vec3b& pixel = input.at<cv::Vec3b>(i, j);
            unsigned char gray = static_cast<unsigned char>(
                pixel[2] * 0.299 + pixel[1] * 0.587 + pixel[0] * 0.114);
            output.at<unsigned char>(i, j) = gray;
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <ImagenEntrada> <ImagenSalida>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    // Cargar la imagen
    cv::Mat image = cv::imread(inputFile, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error al abrir la imagen: " << inputFile << "\n";
        return 1;
    }

    // Crear una matriz para la imagen en escala de grises
    cv::Mat grayImage;

    // Convertir la imagen a escala de grises
    convertToGrayscale(image, grayImage);

    // Guardar la imagen procesada
    if (!cv::imwrite(outputFile, grayImage)) {
        std::cerr << "Error al guardar la imagen: " << outputFile << "\n";
        return 1;
    }

    return 0;
}


