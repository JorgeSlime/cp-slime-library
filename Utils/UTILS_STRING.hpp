inline namespace STRING_UTILS{
//CONVERSIONS
template<typename T> 
T to_int(const std::string& s){
    T val = 0; 
    std::stringstream conv(s);
    conv>>val;
    return val;
}
// FOR int to string usar : std::to_string();
template<typename T> 
std::string to_string2(T& val){
    std::stringstream conv;
    conv<<val;
    return conv.str();
}
//SPLITS 
//h,o,l,a , -> h o l a
std::vector<std::string> split(const std::string &s,char sep){
    std::stringstream ss(s);
    std::string tmp;
    std::vector<std::string> text;
    while(std::getline(ss,tmp,sep)){ 
        if(!tmp.empty())
            text.emplace_back(tmp);
    }
    return text;
}
//h__o__l__a __ -> h o l a
std::vector<std::string> split(const std::string &str, const std::string &sep) { 
    std::vector<std::string> text;
    size_t start = 0;
    size_t end = str.find(sep);
    while (end != std::string::npos) {
        std::string tmp= str.substr(start, end - start);
        if (!tmp.empty()) {
            text.emplace_back(tmp);
        }
        start = end + sz(sep);
        end = str.find(sep, start);
    }
    std::string lasttmp = str.substr(start);
    if (!lasttmp.empty()) {
        text.emplace_back(lasttmp);
    }
    return text;
}
// Convert Decimal to any base
std::string decimal_to_any_base(i64 decimal, i64 base){
    if(decimal == 0) return "0";
    std::string num = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    do{
        result.push_back(num[decimal % base]);
        decimal /= base;
    }while(decimal != 0);
    return std::string(result.rbegin(), result.rend());
}
// Convert any base to decimal
i64 any_base_to_decimal(std::string str, int base) {
    auto val = [](char c){
        return (c >= '0' && c <= '9' ? (int) c - '0' : (int) c - 'A' + 10);
    };
    i64 len = (i32)str.size(), power = 1, num = 0, i;
    for (i = len - 1; i >= 0; i--) {
        num += val(str[i]) * power;
        power = power * base;
    }
    return num;
}

}// STRING_UTILS 

