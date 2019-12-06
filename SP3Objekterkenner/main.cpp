

#include "MatlabDataArray.hpp"
#include "MatlabEngine.hpp"
#include <iostream>
using namespace std;
void callFevalgcd() {

    // Pass vector containing MATLAB data array scalar
    using namespace matlab::engine;

    // Start MATLAB engine synchronously
    std::unique_ptr<MATLABEngine> matlabPtr = startMATLAB();

    // Create MATLAB data array factory
    matlab::data::ArrayFactory factory;

    // Pass vector containing 2 scalar args in vector
    std::vector<matlab::data::Array> args({
        factory.createScalar<int16_t>(30),
        factory.createScalar<int16_t>(40) });

    // Call MATLAB function and return result
//    matlab::data::TypedArray<int16_t> result = matlabPtr->feval(u"gcd", args);
    matlabPtr->eval(u"cd C:\\MATLAB");
    int cresult = matlabPtr->feval<int>(u"gcd", 32, 56);
    double dresult = matlabPtr->feval<double>(u"addiere",4.6,5.0);

//    int16_t v = result[0];
    std::cout << "Result: " << dresult << std::endl;

}

int main()
{
    int a;
    cin >> a;
    cout << "Hello World!" << endl;
//    callFevalgcd();
    matlab::data::ArrayFactory factory;
    matlab::data::Array b;
    b=factory.createArray({2,2},{-2.0,-1.0,1.0,2.0});
    double x[2][2]={-2.0,-1.0,1.0,2.0};
    double d=b[0][1];
    cout << d << endl;
    cout << x[0][1] << endl;;

    return 0;
}
