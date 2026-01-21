#!/bin/bash
set -e
set +x

echo "Installing Omake module hooks ..."

# Change the current directory to the directory of this script
cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1

# Move up to Blazium root folder
cd ../..

# Make Blazium and Omake frens
perl -i -pe '
	$in_block = 1 if /class Node : public Object \{/;
	$has_friend = 1 if $in_block && /friend class OmakeFind;/;
	if ($in_block && /protected:/) {
		print "\tfriend class OmakeFind;\n" unless $has_friend;
		$in_block = 0;
	}
' scene/main/node.h

echo "Done!"
