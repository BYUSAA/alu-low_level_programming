# ALU C Programming — Project 2

**Student:** Byusa Mukarage Martin De Poles  
**Student ID:** 811201785  
**Student email:** m.byusa@alustudent.com

This folder contains three C applications demonstrating dynamic data structures, pointers, function pointers, unions, callback dispatch, and memory cleanup.

## Projects

| Folder | Application | Main concepts |
|---|---|---|
| [Project 1 — Academic Analysis](project_1_academic_analysis/) | Dynamic student-record management and academic risk reporting | \`struct\`, dynamic arrays, sorting, searching, function-pointer menu |
| [Project 2 — Text Mining](project_2_text_mining/) | Dynamic paragraph storage and word-frequency analysis | dynamic text buffer, dynamic statistics array, pointer traversal, tokenization, function pointers |
| [Project 3 — IoT Monitoring](project_3_iot_monitoring/) | Sensor simulation and callback-based alert monitoring | \`struct\`, \`union\`, dynamic device array, callback dispatch, custom monitoring |

## Build

Run each command from its corresponding project directory:

\`\`\`sh
# Project 1
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o academic_analysis

# Project 2
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o text_mining

# Project 3
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o iot_monitor
\`\`\`

Run the executable from that directory (for example, \`./academic_analysis\`).

## Automated smoke checks

From the repository root, run:

\`\`\`sh
bash Project_2/tests/run_smoke_tests.sh
\`\`\`

The script compiles all three programs and checks scripted demonstrations. It saves logs under \`Project_2/test-results/\`. These checks do not replace manual review of every menu option, invalid-input case, or allocation-failure path.

## Submission evidence

The \`sample_output.txt\` files are console transcripts, not screenshots. Capture readable screenshots from the final program versions and use output from the final build. Do not report a test as passed unless it has actually been run.
