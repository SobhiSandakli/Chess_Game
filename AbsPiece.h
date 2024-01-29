#include <utility>
#include <stdexcept>
using namespace std;
namespace model 
{
    enum class Color 
    {
        white,
        black
    };

    Class AbsPiece
    {
        public:
            AbsPiece(int x , int y , const Color& color , const string& type );
            virtual ~AbsPiece() = default;

            void move(int x, int y);

            inline pair<int, int> getPosition() const { return std::pair(x_, y_); };

            bool isValidMove (int x, int y) const;

            inline const string& getType() {return type_;};

            inline const string& getColor() {return color_;};

        protected:
            virtual bool isValidPieceMove (int x, int y) const = 0;
            int x_;
            int y_;
            Color color_;
            string type_;
    };
    
}