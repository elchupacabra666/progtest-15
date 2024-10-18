

#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>

using namespace std;

class CDate {
      public:
	//---------------------------------------------------------------------------------------------
	CDate(int y,
	      int m,
	      int d)
		: m_Year(y),
		  m_Month(m),
		  m_Day(d) {
	}

	//---------------------------------------------------------------------------------------------
	int compare(const CDate &x) const {
		if (m_Year != x.m_Year)
			return m_Year - x.m_Year;
		if (m_Month != x.m_Month)
			return m_Month - x.m_Month;
		return m_Day - x.m_Day;
	}

	//---------------------------------------------------------------------------------------------
	int year(void) const {
		return m_Year;
	}

	//---------------------------------------------------------------------------------------------
	int month(void) const {
		return m_Month;
	}

	//---------------------------------------------------------------------------------------------
	int day(void) const {
		return m_Day;
	}

	//---------------------------------------------------------------------------------------------
	friend ostream &operator<<(ostream &os,
				   const CDate &x) {
		char oldFill = os.fill();
		return os << setfill('0') << setw(4) << x.m_Year << "-"
			  << setw(2) << static_cast<int> ( x.m_Month ) << "-"
			  << setw(2) << static_cast<int> ( x.m_Day )
			  << setfill(oldFill);
	}
	//---------------------------------------------------------------------------------------------
      private:
	int16_t m_Year;
	int8_t m_Month;
	int8_t m_Day;
};

#endif /* __PROGTEST__ */
class CInvoice {
      public:
	CInvoice(const CDate &date,
		 const string &seller,
		 const string &buyer,
		 unsigned int amount,
		 double vat) : m_date(date), m_seller(seller), m_buyer(buyer), m_amount(amount), m_vat(vat){};

	CInvoice(const CInvoice &x): m_date(x.m_date), m_seller(x.m_seller), m_buyer(x.m_buyer), m_amount(x.m_amount), m_vat(x.m_vat) {}

	CInvoice &operator=(CInvoice x)
	{
		this->m_date = x.m_date;
		this->m_seller = x.m_seller;
		this->m_buyer = x.m_buyer;
		this->m_amount = x.m_amount;
		this->m_vat = x.m_vat;
		return *this;
	}


	CDate date(void) const {
		return m_date;
	}

	string buyer(void) const {
		return m_buyer;
	}

	string seller(void) const {
		return m_seller;
	}

	unsigned int amount(void) const {
		return m_amount;
	}

	double vat(void) const{
		return m_vat;
	}



      private:
	CDate m_date;
	string m_seller;
	string m_buyer;
	unsigned int m_amount;
	double m_vat;


};

bool operator==(const CInvoice & a, const CInvoice & b) {
	if(((a.date()).compare(b.date()) == 0) && a.seller() == b.seller() && a.buyer() == b.buyer() && a.amount() == b.amount() && a.vat() == b.vat())
		return true;
	return false;
}

class additionalInfo {
      public:
	int m_age = 0;
	bool m_accepted = false;
	bool m_issued = false;

	additionalInfo(){};
	additionalInfo(const int & age, const bool accepted, const bool issued)
		: m_age(age), m_accepted(accepted), m_issued(issued) {}
};


string removeExtraSpaceAndCase(const string & src) {
	string fixed;
	fixed.resize(src.size());
	transform(src.begin(), src.end(), fixed.begin(), ::tolower);
	for (size_t i = 0; i < fixed.size() - 1; i++) {
		if (fixed[i] == ' ' && fixed[i + 1] == ' ') {
			fixed.erase(fixed.begin() + i + 1);
			i--;
		}
	}
	if (fixed[0] == ' ')
		fixed.erase(fixed.begin());
	if (fixed[fixed.size() - 1] == ' ')
		fixed.erase(fixed.end() - 1);
	return fixed;
}




struct CompareBuyer {
	bool operator()(const pair<CInvoice, additionalInfo> &a, const pair<CInvoice, additionalInfo> &b) const {
		string fixedA, fixedB;
		fixedA = removeExtraSpaceAndCase(a.first.buyer());
		fixedB = removeExtraSpaceAndCase(b.first.buyer());
		if (fixedA.compare(fixedB) < 0)
			return true;
		if (fixedA.compare(fixedB) > 0)
			return false;
		fixedA = removeExtraSpaceAndCase(a.first.seller());
		fixedB = removeExtraSpaceAndCase(b.first.seller());
		if (fixedA.compare(fixedB) < 0)
			return true;
		if (fixedA.compare(fixedB) > 0)
			return false;
		if (a.first.amount() < b.first.amount())
			return true;
		if (a.first.amount() > b.first.amount())
			return false;
		if (a.first.vat() < b.first.amount())
			return true;
		if (a.first.vat() > b.first.amount())
			return false;
		if (a.first.date().compare(b.first.date()) < 0)
			return true;
		return false;
	}
};

struct CompareSeller {
	bool operator()(const pair<CInvoice, additionalInfo> &a, const pair<CInvoice, additionalInfo> &b) const {
		string fixedA, fixedB;
		fixedA = removeExtraSpaceAndCase(a.first.seller());
		fixedB = removeExtraSpaceAndCase(b.first.seller());
		if (fixedA.compare(fixedB) < 0)
			return true;
		if (fixedA.compare(fixedB) > 0)
			return false;
		fixedA = removeExtraSpaceAndCase(a.first.buyer());
		fixedB = removeExtraSpaceAndCase(b.first.buyer());
		if (fixedA.compare(fixedB) < 0)
			return true;
		if (fixedA.compare(fixedB) > 0)
			return false;
		if (a.first.amount() < b.first.amount())
			return true;
		if (a.first.amount() > b.first.amount())
			return false;
		if (a.first.vat() < b.first.amount())
			return true;
		if (a.first.vat() > b.first.amount())
			return false;
		if (a.first.date().compare(b.first.date()) < 0)
			return true;
		return false;
	}
};


struct comparefnc {
	bool operator()(const string & a, const string & b) const {
		if (removeExtraSpaceAndCase(a).compare(removeExtraSpaceAndCase(b)) < 0)
			return true;
		return false;
	}
};




struct company {
	company() = default;

	set<pair<CInvoice, additionalInfo>, CompareBuyer> m_buyer_set;
	set<pair<CInvoice, additionalInfo>, CompareSeller> m_seller_set;

};


class CVATRegister {
      public:
	CVATRegister(void) = default;

	bool registerCompany(const string &name);

	bool addIssued(const CInvoice &x);

	bool addAccepted(const CInvoice &x);

	bool delIssued(const CInvoice &x);

	bool delAccepted(const CInvoice &x);

	additionalInfo info;
	map<string, company, comparefnc> companies;


      private:
	// todo
};

bool CVATRegister::registerCompany(const string &name) {
	auto result = companies.emplace(make_pair(name, company()));
	return result.second;
}

bool CVATRegister::addIssued(const CInvoice &x) {
	if (removeExtraSpaceAndCase(x.buyer()).compare(removeExtraSpaceAndCase(x.seller())) == 0)
		return false;
	if (companies.find(x.seller()) == companies.end() || companies.find(x.buyer()) == companies.end())
		return false;

	auto it_company_seller = companies.find(x.seller());
	auto it_company_buyer = companies.find(x.buyer());
	auto it_seller = it_company_seller->second.m_seller_set.find(make_pair(x, additionalInfo(0, false, false)));
	//prvni if
	if (it_seller == it_company_seller->second.m_seller_set.end()) {
		cout << "does not exist" << endl;

		it_company_seller->second.m_seller_set.insert(make_pair(CInvoice(x.date(), it_company_seller->first, it_company_buyer->first, x.amount(), x.vat()), additionalInfo(info.m_age, false, true)));
		it_company_buyer->second.m_buyer_set.insert(make_pair(CInvoice(x.date(), it_company_seller->first, it_company_buyer->first, x.amount(), x.vat()), additionalInfo(info.m_age, false, true)));
		info.m_age++;
		return true;
	}
	if (it_seller->second.m_issued == true) {		//was issued, add nothing
		return false;
	}

	if (it_seller -> second.m_issued == false) {		//does exist, not issued, add

		CInvoice tmp (x.date(), it_company_seller->first, it_company_buyer->first, x.amount(), x.vat());
		auto pair = make_pair(tmp, additionalInfo(it_seller->second.m_age, it_seller->second.m_accepted, true));
		auto it_buyer = it_company_buyer->second.m_buyer_set.find(make_pair(x, additionalInfo(0, false, false)));
		it_company_seller->second.m_seller_set.erase(it_seller);
		it_company_seller->second.m_seller_set.insert(pair);
		it_company_buyer->second.m_buyer_set.erase(it_buyer);
		it_company_buyer->second.m_buyer_set.insert(pair);
		info.m_age++;
		cout << "not issued" << endl;
		return true;
	}
	cout << "never should happen" << endl;
	return false;
}


int main(void) {


	CInvoice a (CDate(2000, 1, 1), "a", "b", 100, 20);
	CInvoice b (CDate(2000, 1, 1), "a", "b", 100, 20);






	CVATRegister r1;
	r1.registerCompany("a");
	r1.registerCompany("b");

	if (r1.addIssued(CInvoice(CDate(2000, 1, 1), "a", "b", 100, 20)))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	/*cout << r1.companies["a"].m_seller_set.begin()->first.seller() << endl;
	cout << r1.companies["a"].m_seller_set.begin()->first.buyer() << endl;
	cout << r1.companies["a"].m_seller_set.begin()->second.m_issued << endl;

	cout << r1.companies["b"].m_buyer_set.begin()->first.seller() << endl;
	cout << r1.companies["b"].m_buyer_set.begin()->first.buyer() << endl;
	cout << r1.companies["b"].m_buyer_set.begin()->second.m_issued << endl;*/

	if (r1.addIssued(CInvoice(CDate(2000, 1, 1), "a", "b", 100, 20)))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	return EXIT_SUCCESS;
}