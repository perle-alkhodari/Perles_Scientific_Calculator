#include "pch.h"
#include "CppUnitTest.h"
#include "../SWE_App/ButtonFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ButtonFactoryTests
{
	TEST_CLASS(ButtonFactoryTests)
	{
	public:
		
		// Checks if the number pad is created correctly
		TEST_METHOD(TestMethod201)
		{
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));

			ButtonFactory buttonFactory(20, 0, 0, 20, 50, parent, 10000);
			buttonFactory.CreateNumberPad();

			bool isMatching = true;

			for (int i = 0; i < 9; i++) {
				wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(i + 10000));
				if (btn->GetLabel() != std::to_string(i + 1)) {
					isMatching = false;
					break;
				}
			}

			Assert::IsTrue(isMatching);
		}

		// Checks if the size of buttons on x is correct
		TEST_METHOD(TestMethod202) {
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));
			ButtonFactory buttonFactory(20, 50, 0, 20, 50, parent, 10000);
			buttonFactory.MakeRow({ "+" });
			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(10000));

			Assert::AreEqual(btn->GetSize().GetX(), 20);
		}

		// Checks if the size on y is correct
		TEST_METHOD(TestMethod203) {
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));
			ButtonFactory buttonFactory(20, 0, 0, 6434, 50, parent, 10000);
			
			buttonFactory.MakeRow({ "+" });
			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(10000));

			Assert::AreEqual(btn->GetSize().GetY(), 50);
		}

		// checks if the next row function works by getting the right new position hafter using it
		TEST_METHOD(TestMethod204) {
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));
			ButtonFactory buttonFactory(20, 0, 0, 10, 10, parent, 10000);

			buttonFactory.MakeRow({ "+" });
			buttonFactory.NextRow();
			buttonFactory.MakeRow({ "-" });
			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(10001));

			Assert::AreEqual(btn->GetPosition().x, 40);
		}

		// checks if the set button size works
		TEST_METHOD(TestMethod205)
		{
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));

			ButtonFactory buttonFactory(20, 10, 0, 20, 50, parent, 20000);
			buttonFactory.SetButtonSizeX(30);
			buttonFactory.MakeRow({ "+" });
			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(20000));

			Assert::AreEqual(btn->GetSize().GetX(), 30);
		}


		// checks if the y position is correct
		TEST_METHOD(TestMethod206)
		{
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));

			ButtonFactory buttonFactory(0, 80, 50, 20, 20, parent, 20001);
			buttonFactory.MakeRow({ "+" });
			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(20001));

			Assert::AreEqual(btn->GetPosition().y, 50);
		}

		// checks if make row, next row and ID incrementing works by 
		// using make row and next row and then checking to see if the correct
		// button is returned when using its expected ID.
		TEST_METHOD(TestMethod207)
		{
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));

			ButtonFactory buttonFactory(5, 5, 5, 5, 5, parent, 20002);
			buttonFactory.MakeRow({ "+" });
			buttonFactory.NextRow();
			buttonFactory.MakeRow({ "+", "-" });

			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(20004));

			Assert::AreEqual(btn->GetLabel(), "-");
		}

		// checking if the buttons end up in the right position after,
		// using make row and next row.

		TEST_METHOD(TestMethod208)
		{
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));

			ButtonFactory buttonFactory(5, 5, 5, 5, 5, parent, 20005);
			buttonFactory.MakeRow({ "+" });
			buttonFactory.NextRow();
			buttonFactory.MakeRow({ "+", "-" });

			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(20007));

			Assert::AreEqual(btn->GetPosition().x, 15);
		}

		// tests if the set starting id method works and if the correct
		// button is returned after using its expected ID.
		TEST_METHOD(TestMethod209)
		{
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));

			ButtonFactory buttonFactory(5, 5, 5, 5, 5, parent, 20009);
			buttonFactory.SetStartingID(20010);
			buttonFactory.MakeRow({ ".", ",", "%" });

			wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(20012));

			Assert::AreEqual(btn->GetLabel(), "%");
		}

		// checks if id incrementing is working as expected.
		TEST_METHOD(TestMethod210)
		{
			wxFrame* parent = new wxFrame(nullptr, wxID_ANY, "", wxPoint(200, 200), wxSize(800, 800));

			ButtonFactory buttonFactory(5, 5, 5, 5, 5, parent, 20013);

			std::vector<std::string>buttonLabels = { "x", "-", "+", "%", "/" };
			bool isIncrementingCorrectly = true;
			buttonFactory.MakeRow(buttonLabels);
			for (int i = 0; i < buttonLabels.size(); i++) {
				wxButton* btn = dynamic_cast<wxButton*>(wxFrame::FindWindowById(20013 + i));
				if (btn->GetLabel() != buttonLabels[i]) {
					isIncrementingCorrectly = false;
				}
			}

			Assert::IsTrue(isIncrementingCorrectly);
		}

	};
}
