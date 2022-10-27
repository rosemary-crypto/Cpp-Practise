// shared_ptr-examples.cpp
// The following examples assume these declarations:
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct MediaAsset
{
    virtual ~MediaAsset() = default; // make it polymorphic
};

struct Song : public MediaAsset
{
    std::wstring artist;
    std::wstring title;
    Song(const std::wstring& artist_, const std::wstring& title_) :
        artist{ artist_ }, title{ title_ } {}
};

struct Photo : public MediaAsset
{
    std::wstring date;
    std::wstring location;
    std::wstring subject;
    Photo(
        const std::wstring& date_,
        const std::wstring& location_,
        const std::wstring& subject_) :
        date{ date_ }, location{ location_ }, subject{ subject_ } {}
};

using namespace std;

int main()
{
// Example 1: The following example shows various ways to declare and initialise a shared_ptr with a new object.
  
  // Use make_shared function when possible.
  auto sp1 = make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");

  // Ok, but slightly less efficient. 
  // Note: Using new expression as constructor argument
  // creates no named variable for other code to access.
  shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));

  // When initialization must be separate from declaration, e.g. class members, 
  // initialize with nullptr to make your programming intent explicit.
  shared_ptr<Song> sp5(nullptr);
  //Equivalent to: shared_ptr<Song> sp5;
  //...
  sp5 = make_shared<Song>(L"Elton John", L"I'm Still Standing");
    
  
// Example 2: The following example shows how to declare and initialize shared_ptr instances that take on shared ownership of an object that has already been allocated by another shared_ptr. 
  
  //Initialize with copy constructor. Increments ref count.
  auto sp3(sp2);

  //Initialize via assignment. Increments ref count.
  auto sp4 = sp2;

  //Initialize with nullptr. sp7 is empty.
  shared_ptr<Song> sp7(nullptr);

  // Initialize with another shared_ptr. sp1 and sp2
  // swap pointers as well as ref counts.
  sp1.swap(sp2);

  
// Example 3: The following example shows how to use the remove_copy_if algorithm on shared_ptr instances in a vector.
  
  vector<shared_ptr<Song>> v {
  make_shared<Song>(L"Bob Dylan", L"The Times They Are A Changing"),
  make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water"),
  make_shared<Song>(L"Thalía", L"Entre El Mar y Una Estrella")
};

  vector<shared_ptr<Song>> v2;
  remove_copy_if(v.begin(), v.end(), back_inserter(v2), [] (shared_ptr<Song> s) 
  {
    return s->artist.compare(L"Bob Dylan") == 0;
  });

  for (const auto& s : v2)
  {
    wcout << s->artist << L":" << s->title << endl;
  }

  
// Example 4: The following example shows how to test the derived type of each element in a vector of shared_ptr of base classes, and then copy the elements and display information about them.
  
  vector<shared_ptr<MediaAsset>> assets {
  make_shared<Song>(L"Himesh Reshammiya", L"Tera Surroor"),
  make_shared<Song>(L"Penaz Masani", L"Tu Dil De De"),
  make_shared<Photo>(L"2011-04-06", L"Redmond, WA", L"Soccer field at Microsoft.")
};

  vector<shared_ptr<MediaAsset>> photos;

  copy_if(assets.begin(), assets.end(), back_inserter(photos), [] (shared_ptr<MediaAsset> p) -> bool
  {
    // Use dynamic_pointer_cast to test whether
    // element is a shared_ptr<Photo>.
    shared_ptr<Photo> temp = dynamic_pointer_cast<Photo>(p);
    return temp.get() != nullptr;
  });

  for (const auto&  p : photos)
  {
    // We know that the photos vector contains only 
    // shared_ptr<Photo> objects, so use static_cast.
    wcout << "Photo location: " << (static_pointer_cast<Photo>(p))->location << endl;
  }

  
// Example 6: The following example shows how shared_ptr overloads various comparison operators to enable pointer comparisons on the memory that is owned by the shared_ptr instances.

  // Initialize two separate raw pointers.
  // Note that they contain the same values.
  auto song1 = new Song(L"Village People", L"YMCA");
  auto song2 = new Song(L"Village People", L"YMCA");

  // Create two unrelated shared_ptrs.
  shared_ptr<Song> p1(song1);    
  shared_ptr<Song> p2(song2);

  // Unrelated shared_ptrs are never equal.
  wcout << "p1 < p2 = " << std::boolalpha << (p1 < p2) << endl;
  wcout << "p1 == p2 = " << std::boolalpha <<(p1 == p2) << endl;

  // Related shared_ptr instances are always equal.
  shared_ptr<Song> p3(p2);
  wcout << "p3 == p2 = " << std::boolalpha << (p3 == p2) << endl; 
  
  return 0;
}