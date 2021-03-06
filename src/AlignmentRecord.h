/* Copyright 2012 Tobias Marschall
 * 
 * This file is part of HaploClique.
 * 
 * HaploClique is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HaploClique is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HaploClique.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALIGNMENTRECORD_H_
#define ALIGNMENTRECORD_H_

#include <string>
#include <set>

#include <bamtools/api/BamAux.h>

#include "Types.h"
#include "ShortDnaSequence.h"
#include "ReadGroups.h"

/** Class that represents alignments of a read pair. */
class AlignmentRecord {
private:
	std::string name;
	unsigned int record_nr;
	int read_group;
	int phred_sum1;
	std::string chrom1;
	unsigned int start1;
	unsigned int end1;
	std::string strand1;
	std::vector<BamTools::CigarOp> cigar1;
	ShortDnaSequence sequence1;
	int phred_sum2;
	std::string chrom2;
	unsigned int start2;
	unsigned int end2;
	std::string strand2;
	std::vector<BamTools::CigarOp> cigar2;
	ShortDnaSequence sequence2;
	double aln_prob;
	double aln_pair_prob_ins_length;
	alignment_id_t id;
	bool single_end;
	std::string line;
	std::set<std::string> readNames;
	int readCount;
	int hcount;

public:
	/** Parse an alignment pair from a line. If no read_group information is available, 
	  * parameter read_groups can be 0. */
	AlignmentRecord(const std::string& line, std::map<std::string,std::string> clique_to_reads, ReadGroups* read_groups = 0);

	unsigned int getRecordNr() const;
	int getPhredSum1() const;
	int getPhredSum2() const;
	
	/** Returns probability that alignment pair is correct based on alignment scores alone. */
	double getProbability() const;
	/** Returns probability that alignment pair is correct based on alignment scores and insert lenghts. */
	double getProbabilityInsertLength() const;

	/** Returns start position of interval associated with this alignment record.
	 *  In case of a single end read, interval corresponds to the alignment;
	 *  in case of a paired end read, interval corresponds to the whole fragment, i.e. first alignment,
	 *  internal segment, and second alignment.
	 */
	unsigned int getIntervalStart() const;
	/** Returns end position of interval associated with this alignment record, see getIntervalStart(). */
	unsigned int getIntervalEnd() const;
	/** Returns length of intersection between two alignments with respect to the intervals given 
	  * by getIntervalStart() and getIntervalEnd(). */
	size_t intersectionLength(const AlignmentRecord& ap) const;

	/** Returns length of intersection between two alignments with respect to the intervals given 
	  * by getInsertStart() and getInsertEnd(). */
	size_t internalSegmentIntersectionLength(const AlignmentRecord& ap) const;

	std::string getChrom1() const;
	std::string getChrom2() const;	
	std::string getChromosome() const;
	unsigned int getEnd1() const;
	unsigned int getEnd2() const;
	std::string getName() const;
	unsigned int getStart1() const;
	unsigned int getStart2() const;
	std::string getStrand1() const;
	std::string getStrand2() const;
	const std::vector<BamTools::CigarOp>& getCigar1() const;
	const std::vector<BamTools::CigarOp>& getCigar2() const;
	const ShortDnaSequence& getSequence1() const;
	const ShortDnaSequence& getSequence2() const;
	int getReadGroup() const;
	double getWeight() const;
	unsigned int getInsertStart() const;
	unsigned int getInsertEnd() const;
	unsigned int getInsertLength() const;
	alignment_id_t getID() const;
	void setID(alignment_id_t id);
	bool isSingleEnd() const;
	bool isPairedEnd() const;
	std::string getLine() const;
	std::set<std::string> getReadNames() const;
	int getReadCount() const;
	int getHCount() const;
	int getCount() const;
};

#endif /* ALIGNMENTRECORD_H_ */
