#pragma once
#include "db.h"
#include "db_base.h"

void qs_init(const char *argv = nullptr);

void qs_update(const char *argv = nullptr);

void qs_search(const char *pattern = nullptr);
