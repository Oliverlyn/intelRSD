/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.intel.podm.rest.odataid;

import com.intel.podm.business.services.context.ContextType;
import org.testng.annotations.Test;

import java.util.HashSet;
import java.util.Set;

import static com.google.common.collect.Sets.newHashSet;
import static com.google.common.collect.Sets.symmetricDifference;
import static com.intel.podm.business.services.context.ContextType.COMPUTER_SYSTEM;
import static com.intel.podm.business.services.context.ContextType.PROCESSOR;
import static com.intel.podm.rest.resources.ResourceNames.ALL_RESOURCE_NAMES;
import static java.util.Arrays.asList;
import static java.util.Collections.emptySet;
import static org.testng.Assert.assertEquals;

public class ContextTypeToResourceNameMapperTest {

    @Test
    public void whenGettingResourceNameForProcessorContext_shouldReturnPodsString() {
        ContextTypeToResourceNameMapper sut = new ContextTypeToResourceNameMapper();
        assertEquals(sut.get(PROCESSOR), "Processors");
    }

    @Test
    public void whenGettingResourceNameForComputerSystemContext_shouldReturnDrivesString() {
        ContextTypeToResourceNameMapper sut = new ContextTypeToResourceNameMapper();
        assertEquals(sut.get(COMPUTER_SYSTEM), "Systems");
    }

    @Test(expectedExceptions = IllegalArgumentException.class)
    public void whenGettingMappedResourceNameForNullContextType_shouldThrow() {
        ContextTypeToResourceNameMapper sut = new ContextTypeToResourceNameMapper();
        sut.get(null);
    }

    @Test
    public void checkWhetherAllContextTypesAreMapped() {
        Set<ContextType> mappedContextTypes = ContextTypeToResourceNameMapper.MAPPING.keySet();
        Set<ContextType> allContextTypes = new HashSet<>(asList(ContextType.values()));

        assertEquals(symmetricDifference(mappedContextTypes, allContextTypes), emptySet());
    }

    @Test
    public void checkWhetherAllCollectionResourceNameAreMapped() {
        Set<String> mappedResourceNames = newHashSet(ContextTypeToResourceNameMapper.MAPPING.values());
        assertEquals(symmetricDifference(mappedResourceNames, ALL_RESOURCE_NAMES), emptySet());
    }
}
