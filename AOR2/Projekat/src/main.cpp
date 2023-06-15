#include <algorithm>
#include <iostream>
#include <optional>
#include <set>
#include <vector>
#include <loaders/bmp.hpp>
#include <loaders/jpeg.hpp>
#include <processors/naiive.hpp>
#include <processors/optimized.hpp>
#include <image.hpp>
#include <timer.hpp>

#ifdef OPTIMIZED_PROCESSOR
using ImageProcessor = OptimizedProcessor;
#else
using ImageProcessor = NaiiveProcessor;
#endif

enum ArgumentState {
    NO_ARG,
    HELP_ARG,
    INPUT_IMAGE_ARG,
    OUTPUT_IMAGE_ARG,
    ADD_ARG,
    SUB_ARG,
    INV_SUB_ARG,
    MUL_ARG,
    DIV_ARG,
    INV_DIV_ARG,
    POW_ARG,
    LOG_ARG,
    ABS_ARG,
    MIN_ARG,
    MAX_ARG,
    INVERSE_ARG,
    GRAYSCALE_ARG,
    FILTER_ARG,
    STATS_ARG
};

struct Argument {
    ArgumentState state;
    std::string description;
    std::set<std::string> aliases;
};

const std::vector<Argument> ARGUMENTS = {
    {HELP_ARG, "Prints this help message and exits.", {"-h", "--help"}},
    {INPUT_IMAGE_ARG, "Loads an image specified by the argument.", {"-i", "-in", "--input"}},
    {ADD_ARG, "Adds the specified argument to all pixels of the image.", {"-add", "--add"}},
    {SUB_ARG, "Subtracts the specified argument from all pixels of the image.", {"-sub", "--sub"}},
    {INV_SUB_ARG, "Subtracts all pixels of the image from the specified argument.", {"-isub", "--inverse-subtract"}},
    {MUL_ARG, "Multiplies all pixels of the image by the specified argument.", {"-mul", "--multiply"}},
    {DIV_ARG, "Divides all pixels of the image by the specified argument.", {"-div", "--divide"}},
    {INV_DIV_ARG, "Divides the specified argument by all pixels of the image.", {"-idiv", "--inverse-divide"}},
    {POW_ARG, "Exponentiates the pixel value of all pixels to the power of the specified argument.", {"-pow", "--power"}},
    {LOG_ARG, "Calculates a logarithm of all pixels of the image with the base of the specified argument.", {"-log", "--log"}},
    {ABS_ARG, "Calculates an absolute value of all pixels of the image.", {"-abs", "--abs"}},
    {MIN_ARG, "Sets all pixels of the image to the minimum of their value and the specified argument.", {"-min", "--min"}},
    {MAX_ARG, "Sets all pixels of the image to the maximum of their value and the specified argument.", {"-max", "--max"}},
    {INVERSE_ARG, "Inverses all pixels of the image.", {"-inv", "--inverse"}},
    {GRAYSCALE_ARG, "Turns all pixels of the image to grayscale.", {"-gs", "-gray", "--grayscale"}},
    {FILTER_ARG, "Applies a specified filter to the image. First argument is the filter width, second is the filter height followed by filter matrix contents, row by row.", {"-filter", "--filter"}},
    {OUTPUT_IMAGE_ARG, "Saves the processed image to the file specified by the argument.", {"-o", "-out", "--out"}},
    {STATS_ARG, "Prints execution statistics.", {"-s", "--stats"}}
};

const Argument& findArgumentByName(const std::string& argName) {
    for (const Argument& arg : ARGUMENTS) {
        if (arg.aliases.find(argName) != arg.aliases.end()) {
            return arg;
        }
    }
    throw std::runtime_error(std::string("Unknown argument: ") + argName);
}

std::string getLowercaseFileExtension(const std::string& filename) {
    std::string fileExtension = filename.substr(filename.find_last_of(".") + 1);
    std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return fileExtension;
}

void checkImage(const std::optional<Image>& image) {
    if (!image.has_value()) {
        throw std::runtime_error("Image has not been loaded. Have you passed an input image beforehand?");
    }
}

float readFloat(const std::string& parameter) {
    if (parameter.empty()) {
        throw std::runtime_error("Missing parameter for the operation.");
    }
    try {
        return std::stof(parameter);
    } catch (std::exception& error) {
        throw std::runtime_error(std::string("Error while converting parameter to float: ") + error.what());
    }
}

#define MEASURE(event, code) \
    do { \
        Timer::start(event); \
        code; \
        Timer::end(event); \
    } while (0)

int main(int argc, char* argv[]) {
    Timer::start("main");
    ArgumentState state = NO_ARG;
    ImageProcessor processor;
    std::optional<Image> image;
    std::string fileExtension;
    float parameter;
    uint32_t filterWidth = UINT32_MAX;
    uint32_t filterHeight = UINT32_MAX;
    std::vector<float> filter;
    try {
        if (argc <= 1) {
            throw std::runtime_error("No arguments were specified. Rerun with -h or --help to see help.");
        }
        for (int i = 1; i <= argc; ++i) {
            const std::string currentArg = (i == argc) ? "" : argv[i];
            ArgumentState nextState = NO_ARG;
            switch (state) {
                case NO_ARG:
                    if (i != argc) {
                        nextState = findArgumentByName(currentArg).state;
                    }
                    break;
                case HELP_ARG:
                    std::cout << "AOR2 project for the school year 2022/2023: image processing application." << std::endl
                              << "Arguments (order is important!):" << std::endl;
                    for (const Argument& arg : ARGUMENTS) {
                        for (const std::string& argName : arg.aliases) {
                            std::cout << "\t" << argName << std::endl;
                        }
                        std::cout << "\t\t" << arg.description << std::endl;
                    }
                    return EXIT_SUCCESS;
                case INPUT_IMAGE_ARG:
                    if (currentArg.empty()) {
                        throw std::runtime_error("Missing filename for the input image (-i, --input).");
                    }
                    if (image.has_value()) {
                        throw std::runtime_error("Image has already been loaded. Have you passed two input images without saving one first?");
                    }
                    Timer::start("input");
                    fileExtension = getLowercaseFileExtension(currentArg);
                    if (fileExtension == "jpg" || fileExtension == "jpeg") {
                        image = JPEGLoader().load(currentArg);
                    } else if (fileExtension == "bmp") {
                        image = BMPLoader().load(currentArg);
                    } else {
                        throw std::runtime_error(std::string("Unsupported file extension (") + fileExtension + ")");
                    }
                    Timer::end("input");
                    break;
                case OUTPUT_IMAGE_ARG:
                    if (currentArg.empty()) {
                        throw std::runtime_error("Missing filename for the output image (-o, --out).");
                    }
                    checkImage(image);
                    Timer::start("output");
                    fileExtension = getLowercaseFileExtension(currentArg);
                    if (fileExtension == "jpg" || fileExtension == "jpeg") {
                        JPEGLoader().save(currentArg, image.value());
                    } else if (fileExtension == "bmp") {
                        BMPLoader().save(currentArg, image.value());
                    } else {
                        throw std::runtime_error(std::string("Unsupported file extension (") + fileExtension + ")");
                    }
                    Timer::end("output");
                    break;
                case ADD_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("add", processor.add(image.value(), parameter));
                    break;
                case SUB_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("sub", processor.sub(image.value(), parameter));
                    break;
                case INV_SUB_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("invsub", processor.invsub(image.value(), parameter));
                    break;
                case MUL_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("mul", processor.mul(image.value(), parameter));
                    break;
                case DIV_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("div", processor.div(image.value(), parameter));
                    break;
                case INV_DIV_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("invdiv", processor.invdiv(image.value(), parameter));
                    break;
                case POW_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("pow", processor.pow(image.value(), parameter));
                    break;
                case LOG_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("log", processor.log(image.value(), parameter));
                    break;
                case ABS_ARG:
                    checkImage(image);
                    MEASURE("abs", processor.abs(image.value()));
                    --i;
                    break;
                case MIN_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("min", processor.min(image.value(), parameter));
                    break;
                case MAX_ARG:
                    checkImage(image);
                    parameter = readFloat(currentArg);
                    MEASURE("max", processor.max(image.value(), parameter));
                    break;
                case INVERSE_ARG:
                    checkImage(image);
                    MEASURE("inverse", processor.inverse(image.value()));
                    --i;
                    break;
                case GRAYSCALE_ARG:
                    checkImage(image);
                    MEASURE("grayscale", processor.grayscale(image.value()));
                    --i;
                    break;
                case FILTER_ARG:
                    if (filterWidth == UINT32_MAX) {
                        checkImage(image);
                        filterWidth = readFloat(currentArg);
                        nextState = FILTER_ARG;
                    } else if (filterHeight == UINT32_MAX) {
                        filterHeight = readFloat(currentArg);
                        filter.reserve(filterWidth * filterHeight);
                        nextState = FILTER_ARG;
                    } else {
                        filter.push_back(readFloat(currentArg));
                        if (filter.size() == filterWidth * filterHeight) {
                            MEASURE("filter", processor.filter(image.value(), filterWidth, filterHeight, filter));
                            filterWidth = UINT32_MAX;
                            filterHeight = UINT32_MAX;
                            filter.clear();
                        } else {
                            nextState = FILTER_ARG;
                        }
                    }
                    break;
                case STATS_ARG:
                    Timer::end("main");
                    Timer::print();
                    Timer::start("main");
                    --i;
                    break;
                default:
                    throw std::runtime_error("FATAL: Unknown application state.");
            }
            state = nextState;
        }
    } catch (std::exception& error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
