#include <libratss/util/BasicCmdLineOptions.h>
#include <libratss/ProjectSN.h>

namespace LIB_RATSS_NAMESPACE {

BasicCmdLineOptions::BasicCmdLineOptions() :
precision(-1),
significands(-1),
snapType(ProjectSN::ST_NONE),
normalize(false),
verbose(false),
progress(false),
inFormat(InputPoint::FM_CARTESIAN),
outFormat(OutputPoint::FM_RATIONAL)
{}

BasicCmdLineOptions::~BasicCmdLineOptions() {}

int BasicCmdLineOptions::parse(int argc, char ** argv) {
	for(int i(1); i < argc; ++i) {
		std::string token(argv[i]);
		if (token == "-p") {
			if (i+1 < argc) {
				precision = ::atoi(argv[i+1]);
				++i;
			}
			else {
				return -1;
			}
		}
		else if (token == "-e") {
			if (i+1 < argc) {
				significands = ::atoi(argv[i+1]);
				++i;
			}
			else {
				return -1;
			}
		}
		else if (token == "-r") {
			if (i+1 < argc) {
				std::string stStr(argv[i+1]);
				if (stStr == "cf") {
					snapType |= ProjectSN::ST_CF;
				}
				else if (stStr == "fx") {
					snapType |= ProjectSN::ST_FX;
				}
				else if (stStr == "fl") {
					snapType |= ProjectSN::ST_FL;
				}
				else if ( stStr == "jp") {
					snapType |= ProjectSN::ST_JP;
				}
				else {
					std::cerr << "Unrecognized snap method: " << stStr << std::endl;
					return -1;
				}
				++i;
			}
			else {
				return -1;
			}
		}
		else if (token == "-s") {
			if (i+1 < argc) {
				std::string stStr(argv[i+1]);
				if (stStr == "p" || stStr == "plane") {
					snapType &= ~ProjectSN::ST_SPHERE;
					snapType |= ProjectSN::ST_PLANE;
				}
				else if (stStr == "s" || stStr == "sphere") {
					snapType |= ProjectSN::ST_SPHERE;
					snapType &= ~ProjectSN::ST_PLANE;
				}
				else {
					std::cerr << "Unrecognized snap location: " << stStr << std::endl;
					return -1;
				}
				++i;
			}
			else {
				return -1;
			}
		}
		else if (token == "-i") {
			if (i+1 < argc) {
				inFileName.assign(argv[i+1]);
				++i;
			}
			else {
				std::cerr << "Unrecognized ";
				return -1;
			}
		}
		else if (token == "-o") {
			if (i+1 < argc) {
				outFileName.assign(argv[i+1]);
				++i;
			}
			else {
				return -1;
			}
		}
		else if (token == "-if") {
			if (i+1 < argc) {
				std::string stStr(argv[i+1]);
				if (stStr == "geo" ) {
					inFormat = InputPoint::FM_GEO;
				}
				else if (stStr == "spherical") {
					inFormat = InputPoint::FM_SPHERICAL;
				}
				else if (stStr == "cartesian") {
					inFormat = InputPoint::FM_CARTESIAN;
				}
				else {
					std::cerr << "Unrecognized input format: " << stStr << std::endl;
				}
				++i;
			}
			else {
				return -1;
			}
		}
		else if (token == "-of") {
			if (i+1 < argc) {
				std::string stStr(argv[i+1]);
				if (stStr == "rational" || stStr == "rat" || stStr == "r") {
					outFormat = OutputPoint::FM_RATIONAL;
				}
				else if (stStr == "split" || stStr == "sr" || stStr == "s") {
					outFormat = OutputPoint::FM_SPLIT_RATIONAL;
				}
				else if (stStr == "float" || stStr == "double" || stStr == "d" || stStr == "f") {
					outFormat = OutputPoint::FM_FLOAT;
				}
				else if (stStr == "float128" || stStr == "f128") {
					outFormat = OutputPoint::FM_FLOAT128;
				}
				else {
					std::cerr << "Unrecognized output format: " << stStr << std::endl;
				}
				++i;
			}
			else {
				return -1;
			}
		}
		else if (token == "-n") {
			normalize = true;
		}
		else if (token == "-v" || token == "--verbose") {
			verbose = true;
		}
		else if (token == "--progress") {
			progress = true;
		}
		else if (token == "-h" || token == "--help") {
			return 0;
		}
		else {
			bool parseOk = false;
			try {
				parseOk = this->parse(token, i, argc, argv);
			}
			catch (const ParseError & e) {
				std::cerr << e.what() << std::endl;
				return -1;
			}
			
			if (!parseOk) {
				std::cerr << "Unknown command line option: " << token << std::endl;
				return -1;
			}
		}
	}
	
	if (precision < 0) {
		precision = 32;
	}
	
	if (! (snapType & (ProjectSN::ST_PLANE|ProjectSN::ST_SPHERE))) {
		snapType |= ProjectSN::ST_PLANE;
	}
	
	if (! (snapType & (ProjectSN::ST_CF|ProjectSN::ST_FX|ProjectSN::ST_FL))) {
		snapType |= ProjectSN::ST_FX;
	}
	
	return 1;
}

bool BasicCmdLineOptions::parse(const std::string & currentToken,int & i, int argc, char ** argv) {
	return false;
}

void BasicCmdLineOptions::options_help(std::ostream& out) const {
	out <<
		"\t-v\tverbose\n"
		"\t--progress\tprogress indicators\n"
		"\t-p num\tset the precision of the input in bits\n"
		"\t-r (cf|fl|fx|jp)\tset the type of float->rational conversion. fx=fixpoint, cf=continous fraction, fl=floating point, jp=jacobi-perron\n"
		"\t-s (s|sphere|p|plane)\tset where the float->rational conversion should take place\n"
		"\t-n\tnormalize input to length 1\n"
		"\t-if format\tset input format: [geo, spherical, cartesian]\n"
		"\t-of format\tset output format: [rational, split, float]\n"
		"\t-e k\tset manual epsilon to be 2^-k\n"
		"\t-i\tpath to input\n"
		"\t-o\tpath to output";
}

void BasicCmdLineOptions::options_selection(std::ostream& out) const {
	out << "Precision: " << precision << '\n';
	if (significands > 0) {
		out << "Significands: " << significands << '\n';
	}
	out << "Float conversion method: ";
	if (snapType & ratss::ProjectSN::ST_CF) {
		out << "continous fraction";
	}
	else if (snapType & ratss::ProjectSN::ST_FX) {
		out << "fix point";
	}
	else if (snapType & ratss::ProjectSN::ST_FL) {
		out << "floating point";
	}
	out << '\n';
	out << "Float conversion location: " << (snapType & ratss::ProjectSN::ST_SPHERE ? "sphere" : "plane") << '\n';
	out << "Normalize: " << (normalize ? "yes" : "no") << '\n';
	out << "Input format: ";
	if (inFormat == InputPoint::FM_GEO) {
		out << "geo";
	}
	else if (inFormat == InputPoint::FM_SPHERICAL) {
		out << "spherical";
	}
	else if (inFormat == InputPoint::FM_CARTESIAN) {
		out << "cartesian";
	}
	out << '\n';
	out << "Output format: ";
	if (outFormat == OutputPoint::FM_FLOAT) {
		out << "float";
	}
	else if (outFormat == OutputPoint::FM_RATIONAL) {
		out << "rational";
	}
	else if (outFormat == OutputPoint::FM_SPLIT_RATIONAL) {
		out << "rational split by space";
	}
	out << '\n';
	out << "Input file: " << (inFileName.size() ? inFileName : "stdin") << '\n';
	out << "Output file: " << (outFileName.size() ? outFileName : "stdout");
}


}//end namespace LIB_RATSS_NAMESPACE