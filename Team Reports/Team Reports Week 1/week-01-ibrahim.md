What I Worked On This Week
For our first week, I focused on mapping out the initial design for the 
Matrix module. Most of my time went into sketching the Matrix API, 
figuring out the most efficient way to store our matrix data, and 
establishing the formal rules for handling different matrix dimensions.
What's Completed
• API Design: Proposed the core interface for the Matrix class
• Data Structure: Decided to go with row-major storage utilizing a 
std::vector<double>.
• Indexing & Math Rules: Defined standard zero-based indexing alongside 
the dimension constraints for addition, subtraction, and multiplication.
• Behavior Rules: Outlined exactly how we will handle transpose 
operations and square matrices.
• Error Checking & Testing: Listed the invalid inputs we need to guard 
against and drafted the initial validation cases to use during testing.
