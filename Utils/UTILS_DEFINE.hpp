inline namespace UTILS_DEFINE{
template <typename T>
inline void UNIQUE(std::vector<T> &x) {
    std::ranges::sort(x);   
    x.erase(std::ranges::unique(x).begin(), x.end());  
    x.shrink_to_fit();  
}
template<typename T> 
inline auto LB(const std::vector<T>& ar,T x,bool pos = true){
    auto it = std::ranges::lower_bound(ar,x); 
    return pos ? std::distance(begin(ar),it) : *it ;
}
template<typename T>
inline auto UB(const std::vector<T>& ar,T x,bool pos = true){
    auto it = std::ranges::upper_bound(ar,x); 
    return pos ? std::distance(begin(ar),it) : *it ;
}
// ordena los valores por el indice
template <typename T>
std::vector<i32> argsort(const std::vector<T> &nums) {
    auto indices = std::vector<i32>(sz(nums));
    std::iota(begin(indices),end(indices),0);
    std::ranges::sort(indices, [&](i32 i, i32 j) {
        return (nums[i] == nums[j] ? i < j : nums[i] < nums[j]);
    });
    return indices;
}
// ordena el array por indice de I
template <typename T>
std::vector<T> rearrange(const std::vector<T> &nums, const std::vector<i32> &I) {
    std::vector<T> copy(sz(I));
    for(i32 i = 0; i < sz(nums) ; i++) copy[i] = nums[I[i]];
    return copy;
}
template<typename T> inline auto MIN(std::span<T> nums, bool pos = false) {
    auto it = std::ranges::min_element(nums);
    return pos ? std::distance(begin(nums), it) : *it;
}
template<typename T> inline auto MAX(std::span<T> nums, bool pos = false) {
    auto it = std::ranges::max_element(nums);
    return pos ? std::distance(begin(nums), it) : *it;
}
} //namespace UTILS_DEFINE 

