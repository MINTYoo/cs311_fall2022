/********************************
The following mySwap works like the swap function in the library.

Your name: Ruben Cerda
Your programmer number: 7
Hours spent: 0 hours and 10 minutes
Any difficulties?: none
********************************/

template <class T>
const T& mySwap(T& x, T& y)
{
  T temp = x;
  x=y;
  y=temp;
}
