#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

void convertToGrayscaleSection(cv::Mat& input, cv::Mat& output, int startRow, int endRow) {
    for (int i = startRow; i < endRow; ++i) {
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

    cv::Mat image = cv::imread(inputFile, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error al abrir la imagen: " << inputFile << "\n";
        return 1;
    }

    cv::Mat grayImage(image.size(), CV_8UC1);

    const int numThreads = 4;  // Ajusta este número según el número de hilos que desees utilizar
    std::vector<std::thread> threads(numThreads);

    int rowsPerThread = image.rows / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? image.rows : (i + 1) * rowsPerThread;
        threads[i] = std::thread(convertToGrayscaleSection, std::ref(image), std::ref(grayImage), startRow, endRow);
    }

    for (auto& t : threads) {
        t.join();
    }

    if (!cv::imwrite(outputFile, grayImage)) {
        std::cerr << "Error al guardar la imagen: " << outputFile << "\n";
        return 1;
    }

    return 0;
}

