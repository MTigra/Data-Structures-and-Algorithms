/**
 * @author Nikita
 * @date 04.04.2017
 * Higher School of Economics,
 * Faculty of Computer Science,
 * Department of Software Engineering
 */

#include "JournalNetActivity.h"

#include <fstream>

template<int numLevels>
JournalNetActivity<numLevels>::JournalNetActivity(void)
{
}

template<int numLevels>
JournalNetActivity<numLevels>::~JournalNetActivity(void)
{}

// Read the whole log from the file on fullpath
template<int numLevels>
void JournalNetActivity<numLevels>::parseLog(string fullpath)
{
    ifstream fin(fullpath); // opens the file

    TimeStamp timestamp; // dummy
    NetActivity netactivity; // dummy

    while (fin)
    {
        fin >> timestamp;
        if (!fin) break;
        fin >> netactivity.m_user;
        if (!fin) break;
        fin >> netactivity.m_host;
        if (!fin) break;

        m_Journal.insert(netactivity, timestamp);
    }
}

// Just dumps the whole journal to the out stream
template<int numLevels>
void JournalNetActivity<numLevels>::dumpJournal(ostream& out)
{
    typename TypeList::TypeNode* prehead, * run;
    prehead = m_Journal.getPreHead();
    run = prehead;

    // prehead is placed before the first and after the last element
    // So it serves two roles.
    while (run->m_next != prehead)
    {
        run = run->m_next;
        out << run->m_key;
        out << " ";
        out << run->m_value;
    }
}

// Outputs all net activity between from and to
template<int numLevels>
void JournalNetActivity<numLevels>::outputSuspiciousActivities(
        string hostSuspicious, const TimeStamp& timeFrom, const TimeStamp& timeTo) const
{
    // Find the starting node
    typename TypeList::TypeNode* node = m_Journal.findLastLessThan(timeFrom)->m_next;

    // Continue while the node is in the defined time frame
    while (!(node->m_key < timeFrom) && node->m_key <= timeTo && node != m_Journal.getPreHead())
    {
        // Check if the host was suspicious
        if (node->m_value.m_host == hostSuspicious)
            // If so, printout the details
            cout << node->m_key << " " << node->m_value << endl;

        // Move to the next log
        node = node->m_next;
    }
}