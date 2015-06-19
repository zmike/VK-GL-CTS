/*-------------------------------------------------------------------------
 * dEQP glslang integration
 * ------------------------
 *
 * Copyright 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *//*!
 * \file
 * \brief glslang OS interface.
 *//*--------------------------------------------------------------------*/

#include "osinclude.h"

namespace glslang
{

// Thread-local

OS_TLSIndex OS_AllocTLSIndex (void)
{
	return deThreadLocal_create();
}

bool OS_SetTLSValue (OS_TLSIndex nIndex, void* lpvValue)
{
	deThreadLocal_set(nIndex, lpvValue);
	return true;
}

bool OS_FreeTLSIndex (OS_TLSIndex nIndex)
{
	deThreadLocal_destroy(nIndex);
	return true;
}

void* OS_GetTLSValue (OS_TLSIndex nIndex)
{
	return deThreadLocal_get(nIndex);
}

// Global lock - not used

void InitGlobalLock (void)
{
}

void GetGlobalLock (void)
{
}

void ReleaseGlobalLock (void)
{
}

// Threading

DE_STATIC_ASSERT(sizeof(void*) >= sizeof(deThread));

void* OS_CreateThread (TThreadEntrypoint entry)
{
	return (void*)(deUintptr)deThread_create(entry, DE_NULL, DE_NULL);
}

void OS_WaitForAllThreads (void* threads, int numThreads)
{
	for (int ndx = 0; ndx < numThreads; ndx++)
	{
		const deThread thread = (deThread)(deUintptr)((void**)threads)[ndx];
		deThread_join(thread);
		deThread_destroy(thread);
	}
}

void OS_Sleep (int milliseconds)
{
	deSleep(milliseconds);
}

void OS_DumpMemoryCounters (void)
{
	// Not used
}

} // glslang
