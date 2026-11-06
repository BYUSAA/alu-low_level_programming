# Project 2 — Final Submission and Demonstration Checklist

**Student:** Byusa Mukarage Martin De Poles  
**Student ID:** 811201785  
**Course:** C Programming

This checklist maps the three programs to the implementation evidence a reviewer can inspect. It is a preparation aid, not a claim that every item has already been demonstrated or awarded marks.

## 1. Build verification

From the repository root, run:

```sh
gcc --version
gcc -std=c99 -Wall -Wextra -Werror -pedantic Project_2/project_1_academic_analysis/main.c -o /tmp/academic_analysis
gcc -std=c99 -Wall -Wextra -Werror -pedantic Project_2/project_2_text_mining/main.c -o /tmp/text_mining
gcc -std=c99 -Wall -Wextra -Werror -pedantic Project_2/project_3_iot_monitoring/main.c -o /tmp/iot_monitor
bash Project_2/tests/run_smoke_tests.sh
```

The smoke-test script compiles the three programs and exercises selected end-to-end paths. It is not a substitute for manually checking every menu option, malformed input, or allocation-failure path.

## 2. Program-to-requirement map

### Project 1 — Academic Performance and Risk Analysis

Inspect `project_1_academic_analysis/main.c`:

- `Student` and `StudentList` structures hold student data and a dynamically allocated array.
- `malloc` allocates the initial records; `realloc` grows the list when a record is added.
- Pointer traversal is used to display and analyse records.
- The menu is dispatched through a table of function pointers.
- Add, duplicate-ID rejection, search, sorting, average, top-student, removal, and summary operations are available.
- Grade validation rejects values outside 0–100 and non-finite values such as `nan` and `inf`.
- The Academic Risk Index is documented in `analysis_explanation.md`; its thresholds are explicitly described as coursework assumptions, not official ALU policy.
- Allocated student memory is released on normal exit.

**Recommended live demonstration:** display the initial records; add a new student; display the new record; remove that student; show the summary and risk analysis; exit and show the memory-release message.

### Project 2 — Text Mining and Linguistic Pattern Analysis

Inspect `project_2_text_mining/main.c`:

- The paragraph is read into a dynamically growing text buffer.
- Word statistics are stored in a dynamically growing array of structures.
- The program traverses text using pointers, normalises alphabetic tokens to lowercase, and counts total and distinct words.
- A function-pointer table dispatches the analysis menu.
- The user can count words, find longest and most frequent words, display and sort frequencies, search, and generate a summary.
- The Lexical Diversity Score is calculated as distinct words divided by total words, multiplied by 100.
- Memory-inspection output displays addresses for the text buffer and statistics array.
- Both allocated arrays are released before exit.

The supplied `source_text.txt` is the selected published source passage. Its source and public-domain context should be retained with the submission. The tokenizer treats alphabetic runs as words; punctuation, whitespace, apostrophes, and hyphens separate tokens. Tokens longer than the fixed display field are truncated, as documented in the source comments.

**Recommended live demonstration:** paste the supplied passage, finish input with a single period on its own line, display word statistics, search for a word known to occur in the passage, generate the summary, inspect memory addresses, and exit.

### Project 3 — IoT Event Monitoring and Callback Engine

Inspect `project_3_iot_monitoring/main.c`:

- A dynamically allocated device array stores registered sensors.
- `SensorReading` is a union containing temperature, pressure, and battery-voltage readings.
- Each sensor type is processed by its own callback: `temperature_monitor`, `pressure_monitor`, or `battery_monitor`.
- The custom `rapid_temperature_change_detector` callback is dispatched through a function pointer and compares consecutive temperature readings.
- The simulator can generate at least 10 readings and reports normal/abnormal readings and alert counts.
- Device registration rejects duplicate IDs; device removal and memory cleanup are implemented.
- The operating ranges and custom callback threshold are documented as illustrative coursework assumptions, not industrial safety standards.

**Recommended live demonstration:** register one temperature sensor, one pressure sensor, and one battery monitor; simulate 10 readings; display current alerts; generate the monitoring summary; remove one device; display the remaining devices; exit.

## 3. Screenshots to capture from your own final run

Capture genuine screenshots from the compiled programs. Keep the terminal readable and include the command or program title where possible. Do not use the illustrative transcripts as if they were screenshots.

- [ ] Project 1: initial records and menu.
- [ ] Project 1: successful add, then display showing the added record.
- [ ] Project 1: successful removal and updated record count.
- [ ] Project 1: summary report and Academic Risk Index.
- [ ] Project 2: source paragraph accepted and total/distinct word counts.
- [ ] Project 2: word-frequency output and search result.
- [ ] Project 2: lexical-diversity summary.
- [ ] Project 2: memory inspection showing actual addresses from that run.
- [ ] Project 3: three sensor types registered.
- [ ] Project 3: 10-reading simulation showing the three standard callbacks and custom callback alert.
- [ ] Project 3: current alert status and monitoring summary.
- [ ] Project 3: device removal and clean exit.

Save screenshots in a clearly named evidence folder (for example, `Project_2/evidence/`) and refer to them in the final report. Only include screenshots that you personally captured from the final version.

## 4. Final review before upload

- [ ] All three programs compile with the strict flags shown above.
- [ ] The smoke-test script completes successfully on your machine.
- [ ] You have manually tried invalid menu choices and invalid data.
- [ ] You can explain the structures, pointers, dynamic allocation, function pointers, union, callbacks, formulas, and cleanup in your own words.
- [ ] The source passage has its title, author, publication/source information, and word-count requirement verified against the assignment brief.
- [ ] Screenshots show actual final execution, not edited or reconstructed output.
- [ ] The submitted report matches the current code and includes the required student details.
- [ ] You have reviewed the assignment brief and marking rubric one last time.

## 5. Evidence and integrity note

The `sample_output.txt` files are textual reference transcripts. Some contain illustrative output and explanatory notes; pointer addresses are process-specific and must be captured afresh. Automated smoke checks cover selected scenarios only. A passing automated check does not prove every edge case is correct, and this checklist does not guarantee a particular mark.
