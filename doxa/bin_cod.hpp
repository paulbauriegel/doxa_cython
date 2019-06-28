class BinCod {
    public:
        int i_;
        BinCod(int i): i_(i) {};
        BinCod(const BinCod & i): i_(i.i_) {};
        int add(const BinCod & other) 
        {
            return i_ + other.i_;
        }
};
